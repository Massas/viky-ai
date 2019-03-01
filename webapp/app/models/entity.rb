class Entity < ApplicationRecord
  include Positionable
  positionable_ancestor :entities_list

  belongs_to :entities_list, touch: true

  serialize :terms, JSON

  validates :solution, length: { maximum: 2000 }
  validates :solution, presence: true, if: -> { self.auto_solution_enabled }
  validates :terms, length: { maximum: 5000 }, presence: true
  validate :validate_locales_exists
  validate :validate_terms_present

  before_validation :parse_terms
  before_validation :build_solution

  def terms_to_s
    return "" if terms.nil?
    terms.collect { |term|
      if term['locale'] == Locales::ANY
        "#{term['term']}"
      else
        "#{term['term']}:#{term['locale']}"
      end
    }.reject(&:blank?).join("\n")
  end


  private

    def parse_terms
      if terms.is_a?(String) && terms.length <= 5000
        self.terms = EntityTermsParser.new(terms).proceed
      end
    end

    def build_solution
      return unless self.auto_solution_enabled
      return if self.terms.blank?
      if terms.is_a? String
        self.solution = self.terms
      else
        self.solution = self.terms.first['term']
      end
    end

    def validate_locales_exists
      return unless terms.instance_of?(Array)
      locales = entities_list.agent.locales
      terms.each do |json|
        unless locales.include?(json['locale'])
          errors.add(:terms, I18n.t('errors.entity.unknown_locale', current_locale: json['locale']))
        end
      end
    end

    def validate_terms_present
      return unless terms.instance_of?(Array)
      terms.each do |json|
        if json['term'].empty?
          errors.add(:terms, I18n.t('errors.entity.term_abscent'))
        end
      end
    end

end
