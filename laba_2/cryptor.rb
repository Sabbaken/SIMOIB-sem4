class Cryptor
  def initialize(alphabet, shift_value)
    @alphabet = alphabet
    @shift_value = shift_value
  end

  def shift_letter(letter)
    index_in_alphabet = @alphabet.index(letter)
    return "" if index_in_alphabet.nil?
    @alphabet[index_in_alphabet + @shift_value]
  end

  def encode(message)
    message.downcase!
    crypted_message = ""
    message.each_char do |letter|
      crypted_message << shift_letter(letter)
    end
    crypted_message
  end
end
