class ChatStatement < ApplicationRecord
  default_scope { order(created_at: :asc) }

  belongs_to :chat_session

  enum speaker: [:user, :bot]
  enum nature: [:text, :image, :list]

  serialize :content, JSON

  validates :content, presence: true
  validate :content_format

  after_create :notify_bot
  after_create :notify_ui

  def to_html
    ApplicationController.renderer.render(
      partial: "/chat_statements/#{self.nature}",
      locals: { statement: self }
    )
  end


  private

    def notify_bot
      if speaker == "user"
        BotSendUserStatementJob.perform_later(chat_session.id, content['text'])
      end
    end

    def notify_ui
      ActionCable.server.broadcast "chat_session_channel_#{chat_session.user.id}", {
        session_id: chat_session.id,
        action: "display_message",
        message: self.to_html
      }
    end

    def content_format
      return if content.blank?
      case nature
        when 'text'
          statement_text = ChatStatementText.new(content)
          errors.add(:base, statement_text.errors.full_messages.join(', ')) if statement_text.invalid?
        when 'image'
          statement_image = ChatStatementImage.new(content)
          errors.add(:base, statement_image.errors.full_messages.join(', ')) if statement_image.invalid?
        when 'list'
          statement_list = ChatStatementList.new(content)
          errors.add(:base, statement_list.errors.full_messages.join(', ')) if statement_list.invalid?
      end
    end
end

