class ChatbotSearch
  attr_reader :options

  DEFAULT_CRITERIA = {
    'filter_wip' => false,
    'query' => ''
  }.with_indifferent_access.freeze

  def initialize(user, options = {})
    @user = user
    @ui_state = UserUiState.new @user
    @options = build_options(options)
  end

  def self.keys
    ['filter_wip', 'query']
  end

  keys.each do |meth|
    define_method(meth) { options[meth.to_sym] }
  end

  def empty?
    @options[:query] == DEFAULT_CRITERIA[:query] &&
      @options[:filter_wip] == DEFAULT_CRITERIA[:filter_wip]
  end

  def to_hash
    {
      query: @options[:query],
      filter_wip: @options[:filter_wip]
    }
  end

  def save
    @ui_state.chatbot_search = {
      query: @options[:query],
      filter_wip: @options[:filter_wip],
    }
    @ui_state.save
  end

  private
    def build_options(http_options)
      default_options_for_user = @ui_state.chatbot_search
      cleaned_http_options = clean_options(http_options)
      final_options = DEFAULT_CRITERIA.merge(
        default_options_for_user
      ).merge(
        cleaned_http_options
      )
      final_options[:user_id] = @user.id.strip
      final_options
    end

    def clean_options(options)
      result = (options || {}).transform_values do |v|
        v.respond_to?(:strip) ? v.strip : v
      end
      result[:filter_wip] = false if result[:filter_wip] == "false"
      result
    end
end
