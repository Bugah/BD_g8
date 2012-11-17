#!/bin/bash

echo "" > related_words
ruby -rubygems related.rb $1 | ruby sql.rb

