import re

from enum import Enum

class CardEnum(Enum):
    AMEX = "AMEX"
    MASTERCARD = "MASTERCARD"
    VISA = "VISA"
    INVALID = "INVALID"

def main():
  try:
    card = int(input("Number: "))

    if is_valid_card(card):
      print(card_company(card).value)
    else:
      print(CardEnum.INVALID.value)
    
  except:
    print(CardEnum.INVALID.value)

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

  # 合計が10で割り切れるかチェック
  return (sum % 10) == 0

def card_company(card):
  if re.match(r'^3[47][0-9]{13}$', str(card)):
    return CardEnum.AMEX
  elif re.match(r'^5[1-5][0-9]{14}$', str(card)):
    return CardEnum.MASTERCARD
  elif re.match(r'^4[0-9]{12}(?:[0-9]{3})?$', str(card)):
    return CardEnum.VISA
  else:
    return CardEnum.INVALID

if __name__ == "__main__":
  main()