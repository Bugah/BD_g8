# Script para gerar tuplas do SQL no formato ('tag', 'tags relacionadas')...

file_str = gets
final = String.new()

file_str.each_line do |word| 
  new_word = word.split(':')
  final << "('#{new_word[0]}', '#{new_word[1].to_s.gsub("\n","")} '),\n"
end

final.chomp!(",\n") # remove a última vírgula

puts final

