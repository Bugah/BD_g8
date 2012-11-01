beginning = Time.now
    
system('./client -a 127.0.0.1 -p 4202 IMG000001.nor')

puts "Ruby: Time elapsed #{Time.now - beginning} seconds"