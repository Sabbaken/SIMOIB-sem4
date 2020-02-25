require_relative 'cryptor'
require_relative 'decryptor'

ALPHABET = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
crypter = Cryptor.new(ALPHABET, 1)
decryptor = Decryptor.new(ALPHABET)

puts 'Введите сообщение'
message_in_plain_text = gets.chomp

crypted_text = crypter.encode(message_in_plain_text)
decrypted_message, key = decryptor.decode(crypted_text)

puts "Шифрование: #{message_in_plain_text} => #{crypted_text}"
puts "Расшифроване:  #{crypted_text} => #{decrypted_message} "
puts "Ключ: #{key}"