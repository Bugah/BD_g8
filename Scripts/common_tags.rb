#!/usr/bin/ruby -Ku

#### CommonTags ####
#
# Usagem: ruby common_tags.rb <N>
#
# Recebe várias tags na entrada, separadas por espaços, e imprime as N tags
# que aparecem com maior frequencia. Isto pode ser usado para expandir a busca
# por imagem, colocando na entrada as tags das imagens mais proximas da buscada.
# Então, o script irá retornar as tags que mais se repetem, possibilitando
# expandir a busca através destas tags.
#

# Número de tags que serão exibidas
NUM_OF_TAGS = ARGV[0].to_i

if !NUM_OF_TAGS then
  puts "Comando invalido! Usagem: ruby common_tags.rb <tag_count>"
  exit(-1)
end

# Leitura
source = $stdin.gets

# Conta tags
h = Hash.new(0)
source.split.each do |tag|
  tag.downcase!

  tag.gsub!(/[:\ .;,"!\?\)]+$/,"") # Ignora pontuação no final de cada tag
  tag.gsub!(/^[:\ ,"\?\[\(]+/,"") # Ignora pontuação no início de cada tag

   # incrementa frequencia da tag
   h[tag] += 1
end

# ordena e imprime primeiras NUM_OF_TAGS tags
h.sort_by{|tag,count| count}.reverse[0...NUM_OF_TAGS].each { |elem|
  puts "#{elem[0]}"
}

