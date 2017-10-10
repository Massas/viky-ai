# Using docker multi stage (docker >= 17.05)
# https://codefresh.io/blog/node_docker_multistage/

# docker build -t docker-registry.pertimm.corp:50001/voqal.ai/platform/nls .

# ============================================================================
# Compile and package Nls
# ============================================================================
FROM docker-registry.pertimm.corp:50001/pertimm/docker-ebusiness-build-stack AS build_image

ENV OG_REPO_PATH=/builds/pse
ENV OG_TOOL_PATH=${OG_REPO_PATH}/tools
ENV PATH=${OG_TOOL_PATH}/bin:${PATH}

# Optimise : prebuild externale dependencies
ADD products/*.dtd                  /builds/pse/products/
ADD resources/manifest.xml          /builds/pse/resources/manifest.xml
ADD sources/manifest.xml            /builds/pse/sources/manifest.xml
ADD sources/makefile.defs.linux     /builds/pse/sources/makefile.defs.linux
ADD sources/external_dependencies   /builds/pse/sources/external_dependencies
ADD tools                           /builds/pse/tools

RUN buildinit.pl
RUN factory.pl -c external_dependencies redebug

ADD products/bu2_nls/conf           /builds/pse/products/bu2_nls/conf
ADD products/bu2_nls/manifest.xml   /builds/pse/products/bu2_nls/manifest.xml
ADD products/bu2_nls/LICENSE.TXT    /builds/pse/products/bu2_nls/LICENSE.TXT
ADD sources                         /builds/pse/sources

RUN genmake.pl linux64 all
RUN factory.pl -p bu2_nls redebug
RUN factory.pl -s bu2_nls   debug

# ============================================================================
# Test Nls
# ============================================================================
FROM ruby:2.4.2 AS test_image

WORKDIR /tests

# Firstly bundle install (faster build)
ADD products/bu2_nls/tests/Gemfile      /tests
ADD products/bu2_nls/tests/Gemfile.lock /tests

RUN bundle install --jobs $(nproc)

# Copy test code
ADD products/bu2_nls/tests  /tests

COPY --from=build_image /builds/pse/ship /
RUN ln -sfn `readlink -f /nls-* | head -n 1` /nls
ENV NLS_INSTALL_PATH=/nls


# Run Tests
ENV TERM=xterm-256color
RUN bundle exec rake test

# ============================================================================
# Setup a lightweigth image only with minimal binaries
# ============================================================================
FROM ubuntu:xenial AS run_image
WORKDIR /
COPY --from=build_image /builds/pse/ship /
RUN ln -sfn `readlink -f /nls-* | head -n 1` /nls

WORKDIR /nls

EXPOSE 9345
CMD ["./ogm_nls"]
