# coding: ISO-8859-1

# Script para pegar tags relacionadas a partir de thesaurus.

require 'open-uri'
require 'net/http'
require 'nokogiri'

tag = ARGV[0]  

if !tag then
  puts "Comando invalido! Usagem: ruby related.rb <tag>"
  exit(-1)
end

urls = [
    "http://www.merriam-webster.com/thesaurus/"+tag,
    "http://www.urbandictionary.com/thesaurus.php?term="+tag,
    "http://www.dicio.com.br/"+tag+"/"
]
error_msg = [
  "isn't in the thesaurus",
  "find any related words",  
  "foram encontradas palavras na busca por"
]
xpath_str = [
  "(//div[@class='scnt']//span[@class='ssens'])[1]/div[position() <= 2]/a/text()",
  "(//table[@id='entries']//td[@class='word'])/a/text()",
  "//p[@class='adicional sinonimos']//a/text()"
]

related = String.new()

urls.each_index do |i|
  begin
    result = Nokogiri::HTML(open(urls[i]))
    raise if (result.to_s.include? error_msg[i]) 
  rescue
    #puts "_Erro #{tag} (service #{i})"
  else
    xresult = result.xpath(xpath_str[i])

    xresult = xresult.to_a.uniq.join(",").downcase
    xresult.gsub!(' [','')
    xresult.gsub!('],','')
    xresult.gsub!('[,','')
    xresult.gsub!(' ','-')
    xresult.gsub!(',',' ')
  
    related << " " + xresult
  end
end

puts "#{tag}: " + related

