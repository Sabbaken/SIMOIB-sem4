class Decryptor
  def initialize(alphabet)
    @alphabet = alphabet
  end

  def shift_letter(letter, shift_value)
    index_in_alphabet = @alphabet.index(letter)
    return "" if index_in_alphabet.nil?
    @alphabet[index_in_alphabet + shift_value]
  end

  def generate_message(crypted_text, shift_value)
    shift_value = shift_value * (-1)
    decrypted_message = ""

    crypted_text.each_char do |letter|
      decrypted_message << shift_letter(letter, shift_value)
    end
    decrypted_message
  end

  def decode(crypted_text)
    p "Нажмите 's', чтобы остановить процесс перебора"
    p "Нажмите 'z', чтобы вернуться на 1 назад"
    i = -1

    begin
      key_pressed = gets.chomp
      return generate_message(crypted_text, i), i if key_pressed == 's'
      i += 1 unless key_pressed == 'z'

      puts "#{i}: #{generate_message(crypted_text, i)}"
    end while (i < @alphabet.length)

    puts 'Что-то пошло не так 🦕'
    return 'undefined', 'undefined'
  end
end
