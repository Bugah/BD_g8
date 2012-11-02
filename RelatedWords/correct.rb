# Script para remover caracteres especiais (') de um arquivo de texto.
#

file_name = ARGV[0]  

if !file_name then
    puts "Comando invalido! Usagem: correct.rb <file_name>"
      exit(-1)
end
file = File.open(file_name)

file_str = file.read.gsub("'","")
puts file_str
