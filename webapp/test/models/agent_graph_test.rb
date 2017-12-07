require 'test_helper'

class AgentGraphTest < ActiveSupport::TestCase

  test 'Build the graph dependencies : single node' do
    #   A*
    agent_a = create_agent('Agent A')

    graph = agent_a.to_graph

    assert_equal 0, graph.num_edges
    assert_equal 1, graph.num_vertices

    assert graph.has_vertex? agent_a
  end


  test 'Build the graph dependencies : single arc' do
    #   A*
    #  /
    # B
    agent_a = create_agent('Agent A')
    agent_b = create_agent('Agent B')

    AgentArc.create(source: agent_a, target: agent_b)

    graph = agent_a.to_graph

    assert_equal 1, graph.num_edges
    assert_equal 2, graph.num_vertices

    assert graph.has_edge?(agent_a, agent_b)
    assert !graph.has_edge?(agent_b, agent_a)
  end


  test 'Build the graph dependencies : two levels depth' do
    #   A*
    #  /
    # B
    # |
    # D
    agent_a = create_agent('Agent A')
    agent_b = create_agent('Agent B')
    agent_d = create_agent('Agent D')

    AgentArc.create(source: agent_a, target: agent_b)
    AgentArc.create(source: agent_b, target: agent_d)

    graph = agent_a.to_graph

    assert_equal 2, graph.num_edges
    assert_equal 3, graph.num_vertices

    assert graph.has_edge?(agent_a, agent_b)
    assert graph.has_edge?(agent_b, agent_d)
  end


  test 'Build the graph dependencies : two children' do
    #   A*
    #  / \
    # B   C
    agent_a = create_agent('Agent A')
    agent_b = create_agent('Agent B')
    agent_c = create_agent('Agent C')

    AgentArc.create(source: agent_a, target: agent_b)
    AgentArc.create(source: agent_a, target: agent_c)

    graph = agent_a.to_graph

    assert_equal 2, graph.num_edges
    assert_equal 3, graph.num_vertices

    assert graph.has_edge?(agent_a, agent_b)
    assert graph.has_edge?(agent_a, agent_c)
  end


  test 'Build the graph dependencies : ignoring siblings' do
    #  A  B*
    #  \ /
    #   C
    agent_a = create_agent('Agent A')
    agent_b = create_agent('Agent B')
    agent_c = create_agent('Agent C')

    AgentArc.create(source: agent_a, target: agent_c)
    AgentArc.create(source: agent_b, target: agent_c)

    graph = agent_b.to_graph

    assert_equal 1, graph.num_edges
    assert_equal 2, graph.num_vertices

    assert graph.has_edge?(agent_b, agent_c)
  end


  test 'Build the graph dependencies : ignoring parents' do
    #  A  B
    #  \ /
    #   C*
    agent_a = create_agent('Agent A')
    agent_b = create_agent('Agent B')
    agent_c = create_agent('Agent C')

    AgentArc.create(source: agent_a, target: agent_b)
    AgentArc.create(source: agent_a, target: agent_c)

    graph = agent_c.to_graph

    assert_equal 0, graph.num_edges
    assert_equal 1, graph.num_vertices

    assert graph.has_vertex? agent_c
  end


  test 'Build graph dependencies : diamond shape' do
    #   A*
    #  / \
    # B   C
    # | /
    # D
    agent_a = create_agent('Agent A')
    agent_b = create_agent('Agent B')
    agent_c = create_agent('Agent C')
    agent_d = create_agent('Agent D')

    assert AgentArc.create(source: agent_a, target: agent_b)
    assert AgentArc.create(source: agent_a, target: agent_c)
    assert AgentArc.create(source: agent_b, target: agent_d)
    assert AgentArc.create(source: agent_c, target: agent_d)

    graph = agent_a.to_graph

    assert_equal 4, graph.num_edges
    assert_equal 4, graph.num_vertices

    assert graph.has_edge?(agent_a, agent_b)
    assert graph.has_edge?(agent_a, agent_c)
    assert graph.has_edge?(agent_b, agent_d)
    assert graph.has_edge?(agent_c, agent_d)
  end


  test 'Build the graph predecessors : single node' do
    #   A*
    agent_a = create_agent('Agent A')

    graph = agent_a.to_predecessors_graph

    assert_equal 0, graph.num_edges
    assert_equal 1, graph.num_vertices

    assert graph.has_vertex? agent_a
  end


  test 'Build the graph predecessors : single arc' do
    # A
    #  \
    #   B*
    agent_a = create_agent('Agent A')
    agent_b = create_agent('Agent B')

    AgentArc.create(source: agent_a, target: agent_b)

    graph = agent_b.to_predecessors_graph

    assert_equal 1, graph.num_edges
    assert_equal 2, graph.num_vertices

    assert graph.has_edge?(agent_b, agent_a)
    assert !graph.has_edge?(agent_a, agent_b)
  end


  test 'Build the graph predecessors : two levels depth' do
    # A
    #  \
    #   B
    #   |
    #   D*
    agent_a = create_agent('Agent A')
    agent_b = create_agent('Agent B')
    agent_d = create_agent('Agent D')

    AgentArc.create(source: agent_a, target: agent_b)
    AgentArc.create(source: agent_b, target: agent_d)

    graph = agent_d.to_predecessors_graph

    assert_equal 2, graph.num_edges
    assert_equal 3, graph.num_vertices

    assert graph.has_edge?(agent_d, agent_b)
    assert graph.has_edge?(agent_b, agent_a)
  end


  test 'Build the graph predecessors : ignoring siblings' do
    #   A
    #  / \
    # B*  C
    agent_a = create_agent('Agent A')
    agent_b = create_agent('Agent B')
    agent_c = create_agent('Agent C')

    AgentArc.create(source: agent_a, target: agent_b)
    AgentArc.create(source: agent_a, target: agent_c)

    graph = agent_b.to_predecessors_graph

    assert_equal 1, graph.num_edges
    assert_equal 2, graph.num_vertices

    assert graph.has_edge?(agent_b, agent_a)
  end


  test 'Build the graph predecessors : two parents' do
    #  A  B
    #  \ /
    #   C*
    agent_a = create_agent('Agent A')
    agent_b = create_agent('Agent B')
    agent_c = create_agent('Agent C')

    AgentArc.create(source: agent_a, target: agent_c)
    AgentArc.create(source: agent_b, target: agent_c)

    graph = agent_c.to_predecessors_graph

    assert_equal 2, graph.num_edges
    assert_equal 3, graph.num_vertices

    assert graph.has_edge?(agent_c, agent_a)
    assert graph.has_edge?(agent_c, agent_b)
  end


  test 'Build the graph predecessors : ignoring children' do
    #   A*
    #  / \
    # B   C
    agent_a = create_agent('Agent A')
    agent_b = create_agent('Agent B')
    agent_c = create_agent('Agent C')

    AgentArc.create(source: agent_a, target: agent_b)
    AgentArc.create(source: agent_a, target: agent_c)

    graph = agent_a.to_predecessors_graph

    assert_equal 0, graph.num_edges
    assert_equal 1, graph.num_vertices

    assert graph.has_vertex? agent_a
  end


  test 'Build graph predecessors : diamond shape' do
    #   A
    #  / \
    # B   C
    # | /
    # D*
    agent_a = create_agent('Agent A')
    agent_b = create_agent('Agent B')
    agent_c = create_agent('Agent C')
    agent_d = create_agent('Agent D')

    assert AgentArc.create(source: agent_a, target: agent_b)
    assert AgentArc.create(source: agent_a, target: agent_c)
    assert AgentArc.create(source: agent_b, target: agent_d)
    assert AgentArc.create(source: agent_c, target: agent_d)

    graph = agent_d.to_predecessors_graph

    assert_equal 4, graph.num_edges
    assert_equal 4, graph.num_vertices

    assert graph.has_edge?(agent_d, agent_b)
    assert graph.has_edge?(agent_d, agent_c)
    assert graph.has_edge?(agent_b, agent_a)
    assert graph.has_edge?(agent_c, agent_a)
  end


  def create_agent(name)
    agent = Agent.new(
      name: name,
      agentname: name.parameterize
    )
    agent.memberships << Membership.new(user_id: users(:admin).id, rights: 'all')
    assert agent.save
    agent
  end

end
