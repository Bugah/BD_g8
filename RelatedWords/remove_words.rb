# Remove as palavras censuradas de um arquivo de texto, dado na entrada
#
#

file_name = ARGV[0]  

if !tag then
  puts "Comando invalido! Usagem: remove_words.rb <file_name>"
  exit(-1)
end

file = File.open(file_name)
words = ["fart", "poop", "shit", "fuck", "gay", "butt", "penis", "anal", "anus", "arse", "ass", "ballsack", "balls", "bastard", "bitch", "biatch", "bloody", "blowjob", "blow job", "bollock", "bollok", "boner", "boob", "bugger", "bum", "butt", "buttplug", "clitoris", "cock", "coon", "crap", "cunt", "damn", "dick", "dildo", "dyke", "fag", "feck", "fellate", "fellatio", "felching", "fuck", "fudgepacker", "flange", "Goddamn", "God damn", "hell", "homo", "jerk", "jizz", "knobend", "knob end", "labia", "lmao", "lmfao", "muff", "nigger", "nigga", "omg", "penis", "piss", "poop", "prick", "pube", "pussy", "queer", "scrotum", "sex", "shit", "slut", "smegma", "spunk", "tit", "tosser", "turd", "twat", "vagina", "wank", "whore", "wtf", "negro", "asshole", "shit", "sex", "bj", "dick", "poop", "aids", "sexual", "booty", "stupidy", "buttfuck", "analsex", "black-people", "fucked", "mindfuck", "cum", "fucked-up", "fuck-all", "fucking", "fuck-up", "fucked-over", "cluster-fuck", "teen-interacial-sex-club", "mind-fuck", "restofuck", "clusterfuck"]

file_str = file.read

words.each do |word| 
  reg1 = Regexp.new(" " + word + " ")
  reg2 = Regexp.new(" " + word + "'")

  file_str.gsub!(" " + word.to_s + " ",' ')
  file_str.gsub!(reg2,' \'')

end

puts file_str
