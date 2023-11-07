void clear(){
  lcd.clear();
}
void cursor(uint8_t x, uint8_t y){
  lcd.setCursor(x, y);
}

void print(str tampil){
  lcd.print(tampil);
}
void println(str tampil){
  lcd.println(tampil);
}
void print(int tampil){
  lcd.print(tampil);
}
void println(int tampil){
  lcd.println(tampil);
}
