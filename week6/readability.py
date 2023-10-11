text = input("Text: ")

letter_count = 0
word_count = 1
sentence_count = 0

for i in text:
  if i.isalpha():
    letter_count += 1
  elif i.isspace():
    word_count += 1
  elif i == "." or i == "!" or i == "?":
    sentence_count += 1


l = letter_count / word_count * 100
s = sentence_count / word_count * 100
grade =  0.0588 * l - 0.296 * s - 15.8

if grade < 1:
  print("Before Grade 1")
elif grade >= 16:
  print("Grade 16+")
else:
  print("Grade ", round(grade))