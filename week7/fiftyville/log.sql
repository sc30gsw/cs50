--ヒントから盗難の情報を取得するため最初に実行--
SELECT * FROM crime_scene_reports 
  WHERE year = 2020 AND month = 7 AND day = 28 AND street = 'Chamberlin Street';

-- 取得結果 --
-- 295|2020|7|28|チェンバリン・ストリート|CS50アヒルの盗難は午前10時15分にチェンバリン・ストリート裁判所で発生した。 本日、当時その場にいた3人の証人に対してインタビューが行われたが、彼らのインタビュー記録にはそれぞれ裁判所について言及されている。

--最初のSQLの実行により同日の証言を得るため実行--
SELECT * FROM interviews 
  WHERE year = 2020 AND month = 7 AND day = 28;

-- 取得結果（「裁判所」について言及しているもののみメモ） --
-- 161|Ruth|2020|7|28|盗難から10分以内のいつか、私はその泥棒が裁判所の駐車場にある車に乗り込み、走り去るのを見ました。 裁判所の駐車場の防犯映像がある場合は、その時間枠内に駐車場から出た車を探してみるとよいでしょう。
-- 162|ユージーン|2020|7|28|泥棒の名前は知りませんが、見覚えのある人でした。 今朝早く、裁判所に到着する前に、ファイファーストリートのATMの前を歩いていたところ、そこで泥棒がお金を引き出しているのを見ました。
-- 163|Raymond|2020|7|28|泥棒が裁判所から出ようとしていたとき、彼らは誰かに電話をかけ、その人は1分も経たないうちに彼らと話しました。 電話の中で、私は泥棒が明日フィフティビルから一番早い飛行機に乗る予定だと話しているのを聞きました。 その後、窃盗犯は電話の相手に航空券を購入するように頼みました。

-- 証言を元に泥棒を割り出すために裁判所から出た車のプレートを取得 --
SELECT * FROM courthouse_security_logs 
  WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

-- 取得結果 --
-- 260|2020|7|28|10|16|exit|5P2BI95
-- 261|2020|7|28|10|18|exit|94KL13X
-- 262|2020|7|28|10|18|exit|6P58WS2
-- 263|2020|7|28|10|19|exit|4328GD8
-- 264|2020|7|28|10|20|exit|G412CB7
-- 265|2020|7|28|10|21|exit|L93JTIZ
-- 266|2020|7|28|10|23|exit|322W7JE
-- 267|2020|7|28|10|23|exit|0NTHK55

-- 泥棒の候補を絞り込むため、プレートから車の所持者を取得 --
SELECT * FROM people
  WHERE license_plate IN (
    SELECT license_plate FROM courthouse_security_logs 
      WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
  );

-- 取得結果 --
-- 221103|Patrick|(725) 555-4692|2963008352|5P2BI95
-- 243696|Amber|(301) 555-4174|7526138472|6P58WS2
-- 396669|Elizabeth|(829) 555-5269|7049073643|L93JTIZ
-- 398010|Roger|(130) 555-0289|1695452385|G412CB7
-- 467400|Danielle|(389) 555-5198|8496433585|4328GD8
-- 514354|Russell|(770) 555-1861|3592750733|322W7JE
-- 560886|Evelyn|(499) 555-9472|8294398571|0NTHK55
-- 686048|Ernest|(367) 555-5533|5773159633|94KL13X

-- 証言からATMの情報を取得するため --
SELECT * FROM atm_transactions
  WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street';

-- 取得結果
-- 246|28500762|2020|7|28|Fifer Street|withdraw|48
-- 264|28296815|2020|7|28|Fifer Street|withdraw|20
-- 266|76054385|2020|7|28|Fifer Street|withdraw|60
-- 267|49610011|2020|7|28|Fifer Street|withdraw|50
-- 269|16153065|2020|7|28|Fifer Street|withdraw|80
-- 275|86363979|2020|7|28|Fifer Street|deposit|10
-- 288|25506511|2020|7|28|Fifer Street|withdraw|20
-- 313|81061156|2020|7|28|Fifer Street|withdraw|30
-- 336|26013199|2020|7|28|Fifer Street|withdraw|35

-- 口座から泥棒候補を取得するため --
SELECT * FROM people 
  WHERE id IN (
    SELECT person_id FROM bank_accounts 
      WHERE account_number IN (
        SELECT account_number FROM atm_transactions 
          WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw'
      )
  );

-- 取得結果 --
-- 395717|Bobby|(826) 555-1652|9878712108|30G67EN
-- 396669|Elizabeth|(829) 555-5269|7049073643|L93JTIZ
-- 438727|Victoria|(338) 555-6650|9586786673|8X428L0
-- 449774|Madison|(286) 555-6063|1988161715|1106N58
-- 458378|Roy|(122) 555-4581|4408372428|QX4YZN3
-- 467400|Danielle|(389) 555-5198|8496433585|4328GD8
-- 514354|Russell|(770) 555-1861|3592750733|322W7JE
-- 686048|Ernest|(367) 555-5533|5773159633|94KL13X

-- 泥棒候補をさらに絞るため、車両のプレートと口座のSQLで重複している人物を取得 --
 SELECT * FROM people 
  WHERE id IN (
      SELECT person_id FROM bank_accounts 
        WHERE account_number IN (
          SELECT account_number FROM atm_transactions 
            WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw'
        ) 
    INTERSECT 
      SELECT id FROM people 
        WHERE license_plate IN (
          SELECT license_plate FROM courthouse_security_logs 
            WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
        )
  );

-- 取得結果 --
-- 396669|Elizabeth|(829) 555-5269|7049073643|L93JTIZ
-- 467400|Danielle|(389) 555-5198|8496433585|4328GD8
-- 514354|Russell|(770) 555-1861|3592750733|322W7JE
-- 686048|Ernest|(367) 555-5533|5773159633|94KL13X

-- 証言よりFiftyville発のflightsを取得 --
SELECT * FROM flights 
  WHERE origin_airport_id = (
    SELECT id FROM airports 
      WHERE city = 'Fiftyville'
  );

-- 上記のSQLを絞り込み、2020/7/29の一番早いflightsを取得し、行き先を特定するため --
SELECT * FROM flights 
  WHERE origin_airport_id = (
    SELECT id FROM airports 
      WHERE city = 'Fiftyville'
  ) 
  AND year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute;

-- 取得結果
-- 36|8|4|2020|7|29|8|20
-- 43|8|1|2020|7|29|9|30
-- 23|8|11|2020|7|29|12|15
-- 53|8|9|2020|7|29|15|20
-- 18|8|6|2020|7|29|16|0

-- 行き先を特定するため --
SELECT * FROM airports WHERE id = 4;

-- 取得結果
-- 4|LHR|Heathrow Airport|London

-- 乗客の情報をINTERSECTした情報に追加し、泥棒候補をさらに絞り込む --
SELECT * FROM people 
  WHERE passport_number IN (
    SELECT passport_number FROM passengers WHERE flight_id = 36
  ) 
INTERSECT 
    SELECT * FROM people 
      WHERE id IN (
        SELECT person_id FROM bank_accounts 
          WHERE account_number IN (
            SELECT account_number FROM atm_transactions 
              WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw'
          )
      ) 
  INTERSECT 
    SELECT * FROM people 
      WHERE id IN (
        SELECT id FROM people 
          WHERE license_plate IN (
            SELECT license_plate FROM courthouse_security_logs 
              WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
          )
      );

-- 取得結果 --
-- 467400|Danielle|(389) 555-5198|8496433585|4328GD8
-- 686048|Ernest|(367) 555-5533|5773159633|94KL13X

-- それぞれの電話番号で当日の履歴があるか確認 --
SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND caller IN ('(389) 555-5198', '(367) 555-5533');

-- 取得結果 →　泥棒はErnest --
-- 233|(367) 555-5533|(375) 555-8161|2020|7|28|45
-- 236|(367) 555-5533|(344) 555-9601|2020|7|28|120
-- 245|(367) 555-5533|(022) 555-4052|2020|7|28|241
-- 285|(367) 555-5533|(704) 555-5790|2020|7|28|75

-- 証言にある通話時間から共犯者を取得 --
SELECT * FROM people WHERE phone_number IN (
  SELECT receiver FROM phone_calls 
    WHERE year = 2020 AND month = 7 AND day = 28 AND caller = '(367) 555-5533' AND duration < 60
  );

-- 取得結果 → 共犯者はBerthold --
-- 864400|Berthold|(375) 555-8161||4V16VO0