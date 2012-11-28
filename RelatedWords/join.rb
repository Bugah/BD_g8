# Script utilizado para juntar os arquivos finais, e misturar as tags relacionadas deles
# Utiliza hash para isso.

file1 = File.open('related_words_final_merriam').read
file2 = File.open('related_words_final_urbandictionary').read
file3 = File.open('related_words_final_parte_2').read

h = Hash.new("  ")

file1.each_line do |line|
  line = line.split(':')
  h[line[0].to_s] = line[1].to_s
end

file2.each_line do |line|
  line = line.split(':')
  h[line[0].to_s] += line[1].to_s
end

file3.each_line do |line|
  line = line.split(':')
  h[line[0].to_s] += line[1].to_s
end

final = String.new()


h.each do |v,k|
  aux = k.gsub('  ',' ').gsub("\n",'')
  final << "('#{v}', '#{aux}' ),\n"
end

final.chomp!(",\n") # remove a última vírgula

puts final

