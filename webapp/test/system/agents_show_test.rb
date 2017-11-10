require "application_system_test_case"

class AgentsShowTest < ApplicationSystemTestCase

  test 'Navigation to agent show' do
    go_to_agents_index
    click_link "My awesome weather bot admin/weather"
    assert page.has_text?('Agents / My awesome weather bot (admin/weather)')
    assert_equal '/agents/admin/weather', current_path
  end


  test 'Navigation to agent show without rights' do
    admin_login
    visit user_agent_path(users(:confirmed), agents(:weather_confirmed))
    assert page.has_text?("Unauthorized operation.")
  end


  test 'No redirection when configuring from show' do
    go_to_agents_index
    click_link 'My awesome weather bot admin/weather'
    assert page.has_text?('Agents / My awesome weather bot (admin/weather)')
    click_link 'Configure'
    assert page.has_text?('Configure agent')
    click_link 'Cancel'
    assert_equal '/agents/admin/weather', current_path

    click_link 'Configure'
    assert page.has_text?('Configure agent')
    fill_in 'Name', with: 'My new updated weather agent'
    fill_in 'ID', with: 'weather-v2'
    click_button 'Update'
    assert page.has_text?('Agents / My new updated weather agent (admin/weather-v2)')
    assert_equal '/agents/admin/weather-v2', current_path
  end


  test 'Transfer agent ownership' do
    go_to_agents_index
    assert page.has_content?('admin/terminator')
    click_link 'T-800'
    click_link 'Transfer ownership'
    within(".modal") do
      page.execute_script "document.getElementById('input-user-search').value = '#{users('confirmed').id}'"
      click_button 'Transfer'
    end
    assert page.has_text?('Agent T-800 transferred to user confirmed')
    assert_equal '/agents', current_path
    assert page.has_no_content?('admin/terminator')
  end


  test 'Transfer agent ownership whereas another agent with the same agentname throw an error' do
    go_to_agents_index
    assert page.has_content?('admin/weather')
    click_link 'My awesome weather bot'
    click_link 'Transfer ownership'
    within(".modal") do
      page.execute_script "document.getElementById('input-user-search').value = '#{users('confirmed').id}'"
      click_button 'Transfer'
      assert page.has_content?('This user already have an agent with this ID')
    end
  end


  test 'Share from agent show if owner' do
    go_to_agents_index
    click_link 'T-800'
    click_link 'Share'
    click_link 'Invite collaborators'
    assert page.has_content?('Share with')
    within(".modal") do
      page.execute_script "document.getElementById('input-user-search').value = '#{users('confirmed').id}'"
      click_button 'Invite'
    end
    assert page.has_text?('Agent terminator shared with : confirmed.')
    assert_equal '/agents/admin/terminator', current_path
  end


  test 'Cannot share from agent show if not owner' do
    login_as users(:edit_on_agent_weather).email, 'BimBamBoom'

    assert page.has_text?("Agents")

    click_link 'My awesome weather bot'
    assert_equal '/agents/admin/weather', current_path
    assert page.has_no_link?('Share')
  end


  test 'Access to unkown agent' do
    go_to_agents_index
    visit user_agent_path('admin', 'unknown-agent')
    assert_equal '/404', current_path
  end
end