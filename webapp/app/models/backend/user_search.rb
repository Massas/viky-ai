class Backend::UserSearch
  attr_reader :options

  def initialize(options = {})
    @options = options || {}
    @options[:sort_by] = sort_by
  end

  def self.keys
    ["email", "status"]
  end

  keys.each do |meth|
    define_method(meth) { options[meth.to_sym] }
  end

  def sort_by
    options[:sort_by] || "last_action"
  end

  def empty?
    is_empty = true
    options.each do |key, value|
      unless [:sort_by].include?(key)
        is_empty = false unless value.blank?
      end
    end
    return is_empty
  end

end