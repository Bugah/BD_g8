# coding: ISO-8859-1

# Script para pegar tags relacionadas a partir de thesaurus.
# Para mudar de site, é necessário descomentar linhas 16 e 25, 29-31 e comentar linhas 17 e 26.
# (Poderia ter feito isso configurável...)

require 'open-uri'
require 'net/http'
require 'nokogiri'

tag = ARGV[0]  

if !tag then
  puts "Comando invalido! Usagem: related.rb <tag>"
  exit(-1)
end

#url = "http://www.merriam-webster.com/thesaurus/"+tag
url = "http://www.dicio.com.br/"+tag+"/"
#url = "http://www.urbandictionary.com/thesaurus.php?term="+tag

begin
  result = Nokogiri::HTML(open(url))
  raise if (result.to_s.include? "find any related words") 
rescue
  puts "_Erro #{tag}"
else
  #related = result.xpath("(//div[@class='scnt']//span[@class='ssens'])[1]/div[2]/a/text()")
  #related = result.xpath("(//table[@id='entries']//td[@class='word'])/a/text()")
  related = result.xpath("//p[@class='adicional sinonimos']//a/text()")

  related = related.to_a.uniq.join(",").downcase
  related.gsub!(' [','')
  related.gsub!('],','')
  related.gsub!('[,','')
  related.gsub!(' ','-')
  related.gsub!(',',' ')

  puts "#{tag}: " + related
end

