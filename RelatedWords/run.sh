#!/bin/bash

# Pega todas tags de supertags e executa related_words.rb

echo "" > related_words

for word in $(cat super_tags)
do
  if [ ${#word} -ge 20 ]; # ignora palavras com mais que 20 caracteres
  then continue
  fi
  echo "$word..."
  ruby -rubygems related.rb $word >> related_words
done
