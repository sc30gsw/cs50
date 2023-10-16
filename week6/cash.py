while True:
  try:
    change = float(input(("Change owed: ")))
    if change > 0:
      break
    else:
      print("Please enter a positive number")
  
  except:
    print("Please enter a positive number")

coins = 0

# ドルをセントに変換
cents = round(change * 100)

coin_values = [25, 10, 5, 1]

for value in coin_values:
  coins += cents // value
  cents %= value

print(f"Coins needed: {coins}")