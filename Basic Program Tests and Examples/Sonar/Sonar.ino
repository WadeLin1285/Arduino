int trig = 44; // 設定觸發腳位
int echo = 42; // 設定返回訊號腳位
float cm;     // 計算距離結果

//初始化設定

void setup() {
  Serial.begin(9600);
  Serial.println("Sonar Distance Sensor Start");
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

// 高電位脈衝

unsigned long tco () {
  digitalWrite(trig, HIGH);   // 設定高電位
  delayMicroseconds(10);      // 延遲10 us
  digitalWrite(trig,LOW);     // 設定低電位
  return pulseIn(echo, HIGH); // 回傳測量結果
}

// 主程式迴圈

void loop() {
  cm = (float)tco()*0.017;    // 計算前方距離
  Serial.print("Distance ");
  Serial.print(cm);            // 顯示資料
  Serial.println(" cm ;  ");

  delay(100);
}
