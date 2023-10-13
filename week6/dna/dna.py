from sys import argv
import csv

def main():
  if len(argv) != 3:
    print("Usage: python3 dna.py data.csv sequence.txt")
    return

  database, dna_sequence = load_data()

  # csvのDNA部分の列名取得
  sub_sequences = list(database[0].keys())[1:]
  find_matching_name(database, dna_sequence, sub_sequences)

def load_data():
  database = []

  with open(argv[1], "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
      database.append(row)

  with open(argv[2], "r") as file:
    dna_sequence = file.read()

  return database, dna_sequence

def find_matching_longest_str(dna_sequence, sub_sequences):
  # 各STRの最長の一致を探す
  result = {}
  for sub_sequence in sub_sequences:
    result[sub_sequence] = longest_match(dna_sequence, sub_sequence)
  
  return result

def find_matching_name(database, dna_sequence, sub_sequences):
  result = find_matching_longest_str(dna_sequence, sub_sequences)

  # databaseから一致するDNAを見つける
  for person in database:
    match = 0
    for sub_sequence in sub_sequences:
      # STRのカウントが一致するか確認
      if int(person[sub_sequence]) == result[sub_sequence]:
        match += 1

      # すべてのSTRが一致する場合
      if match == len(sub_sequences):
        print(person["name"])
        return

  # 一致するものがない場合
  print("No match")

# sequence内のsub_sequenceの最長実行の長さを返す
def longest_match(sequence, sub_sequence):
  longest_run = 0
  sub_sequence_length = len(sub_sequence)
  sequence_length = len(sequence)

  for i in range(sequence_length - sub_sequence_length + 1):
    count = 0

    # 現在の位置から続くsub_sequenceをカウント
    while (i + count < sequence_length and sequence[i + count : i + count + sub_sequence_length] == sub_sequence):
      count += sub_sequence_length
      longest_run = max(longest_run, count // sub_sequence_length)

  return longest_run

if __name__ == "__main__":
  main()
