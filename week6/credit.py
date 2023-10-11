import re

def main():
  try:
    card = int(input("Number: "))

    if is_valid_card(card):
      card_company(card)
    else:
      print("INVALID")
    
  except:
    print("INVALID")

def is_valid_card(card_number):
  # Luhn Algorithmを使用してカード番号をチェック
  sum = 0

  for i, c in enumerate(reversed(str(card_number))):
    n = int(c)
    # card_numberのインデックスが偶数位置の場合
    if i % 2 == 0:
      sum += n
    # card_numberのインデックスが奇数位置の場合
    else:
      n *= 2
      if n > 9:
        n -= 9

      sum += n

  print(sum)

  # 合計が10で割り切れるかチェック
  return (sum % 10) == 0

def card_company(card):
  if re.match(r'^3[47][0-9]{13}$', str(card)):
    print("AMEX")
  elif re.match(r'^5[1-5][0-9]{14}$', str(card)):
    print("MASTERCARD")
  elif re.match(r'^4[0-9]{12}(?:[0-9]{3})?$', str(card)):
      print("VISA")
  else:
    print("INVALID")

if __name__ == "__main__":
  main()