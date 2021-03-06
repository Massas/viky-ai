class TestCommon < Minitest::Test

  # Generates nicer diffs for complicated, nested values.
  make_my_diffs_pretty!

  def pwd
    Nls::Nls.pwd
  end

  def assert_response_has_error expected_error = "", actual_response = {}, msg = nil

    header = ''
    header = "#{msg} : " if !msg.nil?

    assert !actual_response.nil?, "#{header}actual_response  must not be nil"

    if actual_response.kind_of?(RestClient::ExceptionWithResponse)
      begin
        response_from_exception = JSON.parse(actual_response.response.body)
        errors = response_from_exception["errors"]
      rescue
        errors = [ actual_response.response.body ]
      end
    else
      errors = actual_response["errors"]
    end

    assert !errors.nil?, "#{header}actual_response must contains error : \n#{actual_response.inspect}"
    assert !errors.empty?, "#{header}actual_response errors must not be empty : \n#{actual_response.inspect}}"

    expected_error_found = false
    errors.each do |error|
      if error.include? expected_error
        expected_error_found = true
        break
      end

    end

    assert expected_error_found, "#{header}actual_response must contains error \"#{expected_error}\": \n#{JSON.generate(errors)}"

  end

end
