#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
bool wifiFirstConnected = false;
byte pinD1 = 5;
byte pinD2 = 4;
byte pinD3 = 0;
byte pinD4 = 2;
byte pinD5 = 14;
byte pinD6 = 12;
byte pinD7 = 13;
byte pinD8 = 15;
String uid;
byte pin1;
byte pin2;
byte pin3;
byte pin4;
byte pin5;
byte pin6;
byte pin7;
byte pin8;
byte pin9;
byte pin10;
#define QUOTE(...) #__VA_ARGS__
IPAddress ip(192, 168, 1, 69);
IPAddress gateway(192, 168, 1, 1); // Chỉnh sửa Gateway tại đây 
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 1, 249);
ESP8266WebServer sv(80);
void setup()
{
  Serial.begin(115200);  
  //-----------kết nối wifi-------------
  {
    sv.on("/", [] {
      if (sv.hasArg("ssid") && sv.hasArg("sspass") || sv.hasArg("uid"))
      {
        String tmp = sv.arg("ssid") + "\n" + sv.arg("sspass");
        String uidSto = sv.arg("uid") + "\n";
        SPIFFS.begin();
        File f = SPIFFS.open("wifi", "w");
        if (f) {
          f.write((const uint8_t*)tmp.c_str(), tmp.length());
        }
        f.close();
        File fnew = SPIFFS.open("data", "w");
        if (fnew) {
          fnew.write((const uint8_t*)uidSto.c_str(), uidSto.length());
        }
        fnew.close();
        sv.send(200, "text/plain; charset=utf-8", "Đã thiết lập xong");
        ESP.reset();
      } else{
        sv.send(200, "text/html", QUOTE(
<meta charset = 'utf-8'>
<html>
    <title>Wifi</title>
    <head>
        <script>
            $(document).ready(function(){
              $('[data-toggle="popover"]').popover();   
            });
        </script>
        <style>
           @import url('https://fonts.googleapis.com/css2?family=Anton&display=swap');
            
            * {
                background-color: white;
                font-family: 'Anton', sans-serif;
            }
            h1 {
                color: #207720;
                text-align: center;
            }
            .box {
                width: 640px;
                height: 620px;
                border-radius: 20px;
                background-color: #207720;
                margin-top: 60px;
                margin-left: auto;
                margin-right: auto;
                align-items: center;
                justify-content: center;
                box-shadow: 8px 8px 80px black;
            }
            .box2 {
                width: 640px;
                height: 1520px;
                border-radius: 20px;
                background-color: #207720;
                margin-top: 60px;
                margin-left: auto;
                margin-right: auto;
                align-items: center;
                justify-content: center;
                box-shadow: 8px 8px 80px black;
            }
            .inputbox {
                font-size: 20px;
                margin-top: 20px;
                margin-left: 10px;
                height: 180px;
                width: auto;
                border-radius: 50%;
                justify-content: center;
                background-color:#207720;
            }
            .inbox {
                background-color: #207720;
            }
            .mt-20 {
                margin-top: 20px;
            }
            .ml-20 {
                margin-left: 20px;
                text-align: left;
            }
            input {
                height: 40px;
                width: 300px;
                margin-top:10px;
                border-radius: 10px;
                border: none;
                border-bottom: 1px solid #ddd;
                outline: none;
                opacity: 1;
                color: black;
                font-size: 17px;
            }
            .input1 {
                margin-top: 20px;
            }
            ::placeholder {
                opacity: 1;
                color: #ddd;
                font-size: 20px;
            }
            .btn {
                border: none;
                font-size: 20px;
                color: white;
                height: 40px;
                width: 80px;
                background-color:#EC8C32;
                border-radius: 20px;
                transition: all 0.5s;
            }
            .btn:hover {
                background-color: #26A7FF;
            }
            .text-center {
                text-align: center;
                color: white;
                font-size: 30px;
            }
            .heading {
                color: white;
                font-size: 35px;
                text-align: center;
                border-radius: 50%;
                padding-top: 20px;
            }
            .blue{
                background-color: #268AFF;
            }


            .switch {
            position: relative;
            display: inline-block;
            width: 120px;
            height: 68px;
            }

            .switch input { 
            opacity: 0;
            width: 0;
            height: 0;
            }

            .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            -webkit-transition: .4s;
            transition: .4s;
            }

            .slider:before {
            position: absolute;
            content: "";
            height: 52px;
            width: 52px;
            left: 8px;
            bottom: 8px;
            background-color: white;
            -webkit-transition: .4s;
            transition: .4s;
            }

            input:checked + .slider {
            background-color: #00b842;
            }

            input:focus + .slider {
            box-shadow: 0 0 1px #00b842;
            }

            input:checked + .slider:before {
            -webkit-transform: translateX(52px);
            -ms-transform: translateX(52px);
            transform: translateX(52px);
            }
            /* Rounded sliders */
            .slider.round {
            border-radius: 68px;
            }

            .slider.round:before {
            border-radius: 50%;
            }
            .pin-name1 {
                color: white;
                font-size: 35px;
                margin-left: 10px;
                border-radius: 50%;
                width: 200px;
                padding-top: 20px;
            }
            .box-btn {
                height: 80px;
                width: 100px;
            }
            .pinD1 {
                margin-top: 40px;
                width: 500px;
                height: 100px;
                border-radius: 20px;
                margin-left: 70px;
                border-radius: 20px;
                box-shadow: 4px 4px 40px black;
            }
            .sw1{
                margin-left: 300px;
                margin-top: -89px;
            }
            .orange {
                background-color: #EC8C32;
                border-radius: 20px; 
            }
            .yellow {
                background-color: #EDE83E;
                border-radius: 20px;
            }
            .lightgreen {
                background-color: #45B069;
                border-radius: 20px;
            }
            .lightviolet {
                background-color: #a882f6;
                border-radius: 20px;
            }
            .red {
                background-color: #E25150;
                border-radius: 20px;
            }
            .darkBlue {
                background-color: #4B709A;
            }
            .darkOrange {
                background-color: #ffa23e;
            }
            .ending{
                text-align: center;
                padding-top: 30px;
            }
            .lightergreen {
                background-color: #9FD1B4;
            }
        </style>
    </head>
    <body>
        <div class="box2 blue">
            <div class="heading blue ">Bộ điều khiển IO</div> 
            <div class="pinD1 orange">
                <p class="pin-name1 orange">PIN D1 </p>
                <label class="switch orange sw1">
                    <input type="checkbox" onclick="D1()">
                    <span class="slider round"></span>
                </label>
            </div>
            <div class="pinD1 yellow">
                <p class="pin-name1 yellow">PIN D2 </p>
                <label class="switch yellow sw1">
                    <input type="checkbox" onclick="D2()">
                    <span class="slider round"></span>
                </label>
            </div>
            <div class="pinD1 lightgreen">
                <p class="pin-name1 lightgreen">PIN D3 </p>
                <label class="switch lightgreen sw1">
                    <input type="checkbox" onclick="D3()">
                    <span class="slider round"></span>
                </label>
            </div>
            <div class="pinD1 lightviolet">
                <p class="pin-name1 lightviolet">PIN D4 </p>
                <label class="switch lightviolet sw1">
                    <input type="checkbox" onclick="D4()">
                    <span class="slider round"></span>
                </label>
            </div>
            <div class="pinD1 red">
                <p class="pin-name1 red">PIN D5 </p>
                <label class="switch red sw1">
                    <input type="checkbox" onclick="D5()">
                    <span class="slider round"></span>
                </label>
            </div>
            <div class="pinD1 darkBlue">
                <p class="pin-name1 darkBlue">PIN D6 </p>
                <label class="switch darkBlue sw1">
                    <input type="checkbox" onclick="D6()">
                    <span class="slider round"></span>
                </label>
            </div>
            <div class="pinD1 darkOrange">
                <p class="pin-name1 darkOrange">PIN D7 </p>
                <label class="switch darkOrange sw1">
                    <input type="checkbox" onclick="D7()">
                    <span class="slider round"></span>
                </label>
            </div>
            <div class="pinD1 lightergreen">
                <p class="pin-name1 lightergreen">PIN D8 </p>
                <label class="switch lightergreen sw1">
                    <input type="checkbox" onclick=" D8() ">
                    <span class="slider round"></span>
                </label>
            </div>
            <div class="pinD1 yellow">
                <p class="pin-name1 yellow">PIN D9 </p>
                <label class="switch yellow sw1">
                    <input type="checkbox" onclick=" D9() ">
                    <span class="slider round"></span>
                </label>
            </div>
            <div class="pinD1 red">
                <p class="pin-name1 red">PIN D10 </p>
                <label class="switch red sw1">
                    <input type="checkbox" onclick="D10()">
                    <span class="slider round"></span>
                </label>
            </div>
            </div>            
        <div class="box">
            <div class="heading inbox">Cài đặt Wi-Fi</div>
            <form class="inbox" action='./'>
                <div class="inputbox">
                        <div class="inbox">
                            <input class="input1" type="text" placeholder="SSID" id="wfname" name="ssid"> </input> 
                        </div>  
                        <input type="password" placeholder="Mật khẩu" id="sspass" name="sspass" > </input>   
                    <div class="inbox mt-20">
                        <button class="btn" type="submit" value="OK">Kết nối</button>
                    </div>
                </div>
            </form>
            <div class="text-center inbox">Danh sách wifi</div>  
            <div id='listWifi'></div>
        </div>
        <h3 class="ending">Thư viện Wi-fi Manager được tạo bởi Lương Thanh Trà dành tặng thầy Lê Công Long và CLB KHKT</h3>
    </body>
    <script>
        //xử lí button 
        function D1() {
        var xhttp = new XMLHttpRequest();
        xhttp.open('GET', '/D1.html', true);
        xhttp.send();
        }
        function D2() {
        var xhttp = new XMLHttpRequest();
        xhttp.open('GET', '/D2.html', true);
        xhttp.send();
        }function D3() {
        var xhttp = new XMLHttpRequest();
        xhttp.open('GET', '/D3.html', true);
        xhttp.send();
        }function D4() {
        var xhttp = new XMLHttpRequest();
        xhttp.open('GET', '/D4.html', true);
        xhttp.send();
        }function D5() {
        var xhttp = new XMLHttpRequest();
        xhttp.open('GET', '/D5.html', true);
        xhttp.send();
        }function D6() {
        var xhttp = new XMLHttpRequest();
        xhttp.open('GET', '/D6.html', true);
        xhttp.send();
        }function D7() {
        var xhttp = new XMLHttpRequest();
        xhttp.open('GET', '/D7.html', true);
        xhttp.send();
        }function D8() {
        var xhttp = new XMLHttpRequest();
        xhttp.open('GET', '/D8.html', true);
        xhttp.send();
        }function D9() {
        var xhttp = new XMLHttpRequest();
        xhttp.open('GET', '/D9.html', true);
        xhttp.send();
        }function D10() {
        var xhttp = new XMLHttpRequest();
        xhttp.open('GET', '/D10.html', true);
        xhttp.send();
        }
        //xử lí wifi manager
        window.onload = getData;
        function getData() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {

            var resText = xhttp.responseText.split('|');
            var tmp = '';
            for (i = 0; i < resText.length; i++) {
            tmp = tmp + '<div id = ' + i + ' onclick="setUsr(this)">' + resText[i] +  '</div>' ;
            }
            document.getElementById('listWifi').innerHTML = tmp;
            getData();
        }
        };
        xhttp.open('GET', '/listWifi', true);
        xhttp.send();

    };
    function setUsr(divObj) {
        document.getElementById('wfname').value = divObj.innerHTML;
  }
    </script>
</html>


        ));
      }

    });
    sv.on("/listWifi", [] {
      String list;
      int n = WiFi.scanNetworks();
      if (n == 0) {
        list = "no networks found";
      } else {
        for (int i = 0; i < n; ++i) {
          list += String(WiFi.SSID(i)) + "|";

        }
      }
      sv.send(200, "text/html", list);

    });
    sv.begin();
    String id = "";
    String pass = "";
    uid = "";
    SPIFFS.begin();
    File f = SPIFFS.open("wifi", "r");
    if (f) {
      id = f.readStringUntil('\n');
      pass = f.readString();
    }
    f.close();
    File fnew = SPIFFS.open("data", "r");
    if (fnew) {
      Serial.write(fnew.read());
      uid = fnew.readStringUntil('\n');
    }
    else {
      Serial.println("Khong the mo file!");
    }
    fnew.close();
    WiFi.softAP("ESP8266", "12345678");
    WiFi.config(ip, dns, gateway, subnet);
    delay(500);        
    if ( id != "" && pass != "") {
      Serial.println(String("Đang kết nối: ") + id + " | " + pass);
      WiFi.begin(id, pass);
      while (WiFi.status() != WL_CONNECTED )
      {
        delay(100);
        Serial.print(".");
        sv.handleClient();
      }
      Serial.print(String("Kết nối thành công"));
    }
  }
  Serial.println(WiFi.localIP());
  pinMode(LED_BUILTIN, OUTPUT);
  sv.begin();

  sv.on("/D1.html", [] {
    pin1 +=1;
    if (pin1 > 1) {
      pin1 = 0;
    }
    if (pin1 == 1) {
      digitalWrite(pinD1, HIGH);
    }
    else if (pin1 == 0) {
      digitalWrite(pinD1, LOW);
    }
    sv.send(200, "text/html", " ");
  });
    sv.on("/D2.html", [] {
    pin2 +=1;
    if (pin2 > 1) {
      pin2 = 0;
    }
    if (pin2 == 1) {
      digitalWrite(pinD2, HIGH);
    }
    else if (pin2 == 0) {
      digitalWrite(pinD2, LOW);
    }
    sv.send(200, "text/html", " ");
  });
      sv.on("/D3.html", [] {
    pin3 +=1;
    if (pin3 > 1) {
      pin3 = 0;
    }
    if (pin3 == 1) {
      digitalWrite(pinD3, HIGH);
    }
    else if (pin3 == 0) {
      digitalWrite(pinD3, LOW);
    }
    sv.send(200, "text/html", " ");
  });
      sv.on("/D4.html", [] {
    pin4 +=1;
    if (pin4 > 1) {
      pin4 = 0;
    }
    if (pin4 == 1) {
      digitalWrite(pinD4, HIGH);
    }
    else if (pin4 == 0) {
      digitalWrite(pinD4, LOW);
    }
    sv.send(200, "text/html", " ");
  });
      sv.on("/D5.html", [] {
    pin5 +=1;
    if (pin5 > 1) {
      pin5 = 0;
    }
    if (pin5 == 1) {
      digitalWrite(pinD5, HIGH);
    }
    else if (pin5 == 0) {
      digitalWrite(pinD5, LOW);
    }
    sv.send(200, "text/html", " ");
  });
      sv.on("/D6.html", [] {
    pin6 +=1;
    if (pin6 > 1) {
      pin6 = 0;
    }
    if (pin6 == 1) {
      digitalWrite(pinD6, HIGH);
    }
    else if (pin6 == 0) {
      digitalWrite(pinD6, LOW);
    }
    sv.send(200, "text/html", " ");
  });
      sv.on("/D7.html", [] {
    pin7 +=1;
    if (pin7 > 1) {
      pin7 = 0;
    }
    if (pin7 == 1) {
      digitalWrite(pinD7, HIGH);
    }
    else if (pin7 == 0) {
      digitalWrite(pinD7, LOW);
    }
    sv.send(200, "text/html", " ");
  });
      sv.on("/D8.html", [] {
    pin8 +=1;
    if (pin8 > 1) {
      pin8 = 0;
    }
    if (pin8 == 1) {
      digitalWrite(pinD8, HIGH);
    }
    else if (pin8 == 0) {
      digitalWrite(pinD8, LOW);
    }
    sv.send(200, "text/html", " ");
  });
  pinMode(pinD1, OUTPUT);
  pinMode(pinD2, OUTPUT);
  pinMode(pinD3, OUTPUT);
  pinMode(pinD4, OUTPUT);
  pinMode(pinD5, OUTPUT);
  pinMode(pinD6, OUTPUT);
  pinMode(pinD7, OUTPUT);
  pinMode(pinD8, OUTPUT);
  
}
void loop()
{
  sv.handleClient();
}
