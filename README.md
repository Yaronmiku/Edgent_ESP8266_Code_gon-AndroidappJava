# Edgent_ESP8266_Code_gon-AndroidappJava
Project: 
-> dùng ESP điều kiển + WIFI
-> Sensor dht11 arduino (Kiểm tra độ ẩm- nhiệt độ cây trồng), Sensor Servo SG90 (Kích hoạt máy bơm 
-> Relay (Điều kiển Bật Tắt Bơm nước) +cấp nguồn USB riêng cho… Máy bơm Mini (Tưới cây) 
-> Blynk điều kiển bằng Internet 
-> FireBase tạo DATABASE
Không có cái Simulation khó hình dung, định làm gì

-Chung chung là 
Dây VCC= Dương 
GND= âm 
DAta= nối D2-3 
-Dây âm dương  (2 dây) cắm 1 bên vào 1 nguồn
-Dây data nằm trên Board

Code flow về cái việc dùng relay + bơm nước
-Mong muốn kết quả: Bật tắt bơm nước

Blynk::
bật tắt (ON OFF) relay = bật tắt thay đổi trạng thái
Input là gì=  mới chạy thì relay kích thấp là ra 0v , Mức cao input là 3V
*Cao= ngắt, thấp= mở bơm
xem trạng thái ban đầu - thay đổi mức logic chân D1 và D8, 
thay đổi chân đầu ra = 0v thành 3,3v và ngược lại
*Giả lập: 
Đóng mở 1 thiết bị điện 220V AC

DH11::
DHT đo nhiệt độ độ ẩm
Esp sẽ chuyển dữ liệu này lệ firebase
-cần code thêm
If (độ ẩm > 45) 
   {relay bật}
-Sơ đồ
![image](https://user-images.githubusercontent.com/60863634/231210164-aaa4d669-2e40-4082-abff-406c7dce4da0.png) 
Đỏ chung 1 mạch Dương NGUỒN USB PHỤ
Đen chung 1 mạch Âm NGUỒN USB PHỤ
