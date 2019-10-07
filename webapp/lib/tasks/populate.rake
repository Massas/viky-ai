# frozen_string_literal: true

require_relative 'lib/task'

namespace :populate do
  desc 'Populate you viky with dummy agent for performance tests'
  task :agents, %i[email nb_agents] => [:environment] do |_t, args|
    user = User.find_by_email(args[:email])

    opts = {
      owner: user,
      nb_interpretation: 15,
      nb_formulation: 8,
      nb_entity_list: 5,
      nb_entity_list_entites: 100,
      nb_big_entity_list: 1,
      nb_big_entity_list_entites: 2000
    }

    args[:nb_agents].to_i.times do |i|
      Task::Populate.agent(opts)
      puts "Agent #{i} created"
    end
  end
end

class Task::Populate
  RAND_CORPUS = ('a'..'z').to_a
  def self.quick_rand(size)
    (0...size).map { RAND_CORPUS[rand(RAND_CORPUS.size)] }.join
  end

  def self.agent(opts)
    Nlp::Package.sync_active = false

    owner = opts[:owner]
    agent_name = "populate_#{quick_rand(10)}"
    agent = Agent.new(
      name: agent_name,
      agentname: agent_name,
      description: 'Dummy agent used for populate performance tests',
      visibility: 'is_private',
      memberships: [
        Membership.new(user_id: owner.id, rights: 'all')
      ]
    )
    agent.save!

    interpretations(agent, opts)
    big_entiy_lists(agent, opts)
    entiy_lists(agent, opts)

    Nlp::Package.sync_active = true

    agent.touch
    agent.save
  end

  def self.interpretations(agent, opts)
    last_intent = nil
    before_last = nil

    opts[:nb_interpretation].times do
      intent = Intent.new(
        intentname: quick_rand(10),
        visibility: %w[is_public is_private].sample,
        description: 'Interpretation of the world'
      )
      intent.agent = agent
      intent.save!

      opts[:nb_formulation].times do
        expressions = []
        rand(2..4).times do
          expressions << quick_rand(6)
        end

        interpretation = Interpretation.new(
          expression: expressions.join(' '),
          locale: ['fr', 'en', '*'].sample
        )
        interpretation.intent = intent
        interpretation.save!

        unless last_intent.nil?

          interpretation_alias = InterpretationAlias.new(
            aliasname: 'dummy_a',
            position_start: 0,
            position_end: 6
          )
          interpretation_alias.interpretation = interpretation
          interpretation_alias.interpretation_aliasable = last_intent
          interpretation_alias.save!

        end

        next if before_last.nil?

        interpretation_alias = InterpretationAlias.new(
          aliasname: 'dummy_b',
          position_start: 7,
          position_end: 13
        )
        interpretation_alias.interpretation = interpretation
        interpretation_alias.interpretation_aliasable = before_last
        interpretation_alias.save!
      end

      before_last = last_intent
      last_intent = intent
    end
  end

  def self.entiy_lists(agent, opts)
    opts[:nb_entity_list].times do
      entities_list = EntitiesList.new(
        listname: quick_rand(10),
        description: 'Entities of the world',
        visibility: 'is_private',
        agent: agent,
        proximity: 'glued'
      )
      entities_list.save!

      opts[:nb_entity_list_entites].times do
        terms = []
        rand(1..4).times do
          terms << quick_rand(6)
        end

        entity = Entity.new(
          auto_solution_enabled: true,
          terms: [
            { term: terms.join(' '), locale: ['fr', 'en', '*'].sample }
          ],
          entities_list: entities_list
        )
        entity.save!
      end
    end
  end

  def self.big_entiy_lists(agent, opts)
    opts[:nb_big_entity_list].times do
      entities_list = EntitiesList.new(
        listname: quick_rand(10),
        description: 'Big entities of the world',
        visibility: 'is_private',
        agent: agent,
        proximity: 'glued'
      )
      entities_list.save!

      opts[:nb_big_entity_list_entites].times do
        terms = []
        rand(1..4).times do
          terms << quick_rand(6)
        end

        entity = Entity.new(
          auto_solution_enabled: true,
          terms: [
            { term: terms.join(' '), locale: ['fr', 'en', '*'].sample }
          ],
          entities_list: entities_list
        )
        entity.save!
      end
    end
  end
end
