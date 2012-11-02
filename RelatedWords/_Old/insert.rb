# Script para gerar tuplas do SQL no formato ('tag', 'tags relacionadas')...
# (OBSOLETO! O join.rb faz o mesmo, mas juntando os arquivos!)

file_name = ARGV[0]  

if !file_name then
  puts "Comando invalido! Usagem: insert.rb <file_name>"
  exit(-1)
end

file = File.open(file_name)

file_str = file.read
final = String.new()

file_str.each_line do |word| 
  new_word = word.split(':')
  final << "('#{new_word[0]}', '#{new_word[1].to_s.gsub("\n","")} '),\n"
end

final.chomp!(",\n") # remove a última vírgula

puts final
