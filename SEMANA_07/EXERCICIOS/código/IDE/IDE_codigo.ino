#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#define led_azul  7

//configuração de rede
const char *ssid = "Yasmin.inteli"; //Digite o nome da sua rede aqui
const char *password = "yasminoi"; //Digite a senha da rede, deve conter no mínimo 8 caractéres se não dá erro.
WebServer server(80);

//configuração de rede e do botão para obter a comunicação do frontend com a placa
void setup() {
  Serial.begin(115200);
  pinMode(led_azul, OUTPUT);
  WiFi.softAP(ssid, password); // remova "password" caso não queria que o Wi-Fi tenha senha
  IPAddress ESP_IP = WiFi.softAPIP();
  Serial.print("Wi-Fi: ");
  Serial.println(ssid);
  Serial.print("IP: "); // O IP que aparecer aqui coloque no navegador para acessar a página web do ESP32 que será criada logo abaixo.
  Serial.println(ESP_IP);
  server.begin();
  Serial.println("Servidor Iniciado.");
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}
//Corpo todo do HTML, CSS e JS
  void handleRoot(){
    String html = "";
  html += "<html lang=\"en\">";
  html += "<head>";
  html += "<meta charset=\"UTF-8\">";
  html += "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<title>Jogo Ímpar ou Par</title>";
  html += "</head>";
  html += "<body>";
  html += "<section>";
  html += "<div class=\"iniciar\">";
  html += "<section class=\"section\">";
  html += "<div class=\"principal\">";
  html += "<h1>Você sabia</h1>";
  //p de apresentação (curiosidade) do jogo
  html += "<p>Que além dos humanos, estudos afirmam que abelhas possuem a capacidade de diferenciar quantidades<br>pares e ímpares?<br>Clique no botão abaixo para iniciar o jogo amistoso:<br><br></p>";
  //botão de iniciar jogo
  html += "<button class=\"jogar\"><a href=\"#pagina2\">Iniciar jogo</a></button>";
  html += "</div>";
  html += "</section>";
  html += "</div>";
  html += "<section class=\"section2\">";
  html += "<div id=\"Apresentacao\">";
  html += "<h1>Jogo ímpar ou Par<a name=\"pagina2\"></a></h1>";
  //instruções
  html += "<p class=\"texto\">Escolha se você será o jogador n°1 que corresponde a ímpar e ao campo 1 ou o jogador<br>n°2, correspondente a par e ao campo 2. Insira qualquer número e espere o outro jogador fazer o<br> mesmo para saber o ganhador</p>";
  html += "</div>";
  //imagem vista no front apenas pelo liveServer ou com comandos do prompt
  html += "<img src=\"imagens/Richarlison.png\" alt=\"\" class=\"abelha1\">";
  //imagem vista no front apenas pelo liveServer ou com comandos do prompt
  html += "<img src=\"imagens/Ney.png\" alt=\"\" class=\"abelha2\">";
  html += "<div class=\"centro\">";
  html += "<div id=\"container1\">";
  //dica
  html += "<p>Dica: esconda o valor após inserir</p>";
  // jogador 1, campo 1 e btn 1
  html += "<p id=\"jogador1\">Campo 1 - Jogador ímpar</p>";
  html += "<input class=\"num1\" id=\"campo1\" type=\"number\" required>";
  html += "<button onclick=\"num1()\" id=\"btn1\">Esconder valor</button>";
   // jogador 2, campo 2 e btn 2
  html += "<p id=\"jogador2\">Campo 2 - Jogador Par</p>";
  html += "<input class=\"num2\" id=\"campo2\" type=\"number\" required>";
  //botão que esconde valores
  html += "<button onclick=\"num2()\" id=\"btn2\">Esconder valor</button>";
  html += "<div id=\"container2\">";
  //botão para ver resultado
  html += "<button onclick='clicar()'> Ver resultado</button></a>";
  //botão de reset e que também acende led
  html += "<a href=\"/on\"><button id=\"resetar\" onclick=\"window.location.reload()\">Jogar novamente</button></a>";
  html += "<p>O resultado é:</p>";
  //p vazio que mostra o valor resultado
  html += "<p class=\"resultado\"></p>";
  //p vazio que mostra quem ganhou
  html += "<p class=\"ganhador\"></p>";
  html += "</div>";
  html += "</div>";
  html += "</div>";
  html += "</section>";
  html += "</section>";
  html += "<style>";
  //CSS estilização do background, botões com uso de hover, estilização dos inputs e alteração das imagens presentes
  html += "body {";
  //estilização do corpo do html
  html += "background: linear-gradient(45deg, #006A4E, #EFCC00);";
  html += "font-family: monospace;";
  html += "display: flex;";
  html += "justify-content: center;";
  html += "align-items: center;";
  html += "}";
  html += "min-height: 100vh;";
  html += "}";
  html += "*,";
  html += "*::after {";
  html += "padding: 0;";
  html += "margin: 0;";
  html += "box-sizing: border-box;";
  html += "}";
  html += ".section {";
  html += "display: flex;";
  html += "justify-content: center;";
  html += "align-items: center;";
  html += "width: 100vw;";
  html += "height: 100vh;";
  html += "text-align: center;";
  html += "}";
  //estilizção da seção
  html += ".section2 {";
  html += "width: 100vw;";
  html += "height: 100vh;";
  html += "margin: 30px;";
  html += "}";
  html += "button {";
  html += "border: 3px solid #EFCC00;";
  html += "background-image: linear-gradient(30deg, #006A4E 50%, transparent 50%);";
  html += "background-size: 500px;";
  html += "background-repeat: no-repeat;";
  html += "background-position: 0%;";
  html += "transition: background 300ms ease-in-out;";
  html += "border-radius: 8px;";
  html += "color: #fff;";
  html += "font-family: sans-serif;";
  html += "font-size: 14px;";
  html += "padding: 8px 10px;";
  html += "margin: 4px;";
  html += "}";
  //uso do hover nos botões
  html += "button:hover {";
  html += "background-position: 100%;";
  html += "transition: 1.5s;";
  html += "color: #006A4E;";
  html += "border: 3px solid #EFCC00;";
  html += "}";
  //div centro
  html += ".centro {";
  html += "position: relative;";
  html += "padding: 30px;";
  html += "display: flex;";
  html += "justify-content: center;";
  html += "align-items: center;";
  html += "border-radius: 8px;";
  html += "box-shadow: 0 15px 35px rgb(0, 0, 0);";
  html += "width: 40%;";
  html += "margin-left: auto;";
  html += "margin-right: auto;";
  html += "background-color: #fff;";
  html += "}";
  html += "h1 {";
  html += "text-align: center;";
  html += "font-size: 40px;";
  html += "}";
  html += ".texto {";
  html += "text-align: center;";
  html += "padding: 6px;";
  html += "margin: 5%;";
  html += "font-size: 15px;";
  html += "}";
  html += "p {";
  html += "font-size: 15px;";
  html += "}";
  //imagem
  html += ".abelha {";
  html += "float: right;";
  html += "width: 30%;";
  html += "opacity: 90%;";
  html += "}";
  //imagem
  html += ".abelha1 {";
  html += "float: left;";
  html += "width: 20%;";
  html += "}";
  html += ".abelha2 {";
  html += "float: right;";
  html += "width: 20%;";
  html += "}";
  html += "input {";
  html += "padding: 8px 10px;";
  html += "position: relative;";
  html += "border: none;";
  html += "outline: none;";
  html += "background: linear-gradient(45deg, #006A4E, #EFCC00);";
  html += "color: #000;";
  html += "font-size: 0.9em;";
  html += "letter-spacing: 0.05;";
  html += "}";
  html += "a {";
  html += "text-decoration: none;";
  html += "color: #fff;";
  html += "}";
  //hover do link
  html += "a:hover {";
  html += "color: #006A4E;";
  html += "}";
  html += ".jogar {";
  html += "padding: 15px 17px;";
  html += "}";
  html += "</style>";
  //JavaScript
  html += "<script>";
  html += "function num1() {";
   //esconde o campo 1 onde tem o valor após clicar no botão de esconder
  html += "document.getElementById(\"campo1\").style.display = \"none\";";
  //esconde botão 2
  html += "document.getElementById(\"btn1\").style.display = \"none\";";
  html += "var jogador1 = document.getElementById(\"jogador1\");";
  //após esconder o valor inserido, no frontend é indicado que o primeiro jogador já enviou
  html += "jogador1.innerHTML = \"O jogador 1 fez o envio.\";";
  html += "}";
  html += "function num2() {";
  //esconde o campo 2 onde tem o valor após clicar no botão de esconder
  html += "document.getElementById(\"campo2\").style.display = \"none\";";
  //esconde botão 2
  html += "document.getElementById(\"btn2\").style.display = \"none\";";
  html += "var jogador2 = document.getElementById(\"jogador2\");";
  //após esconder o valor inserido, no frontend é indicado que o segundo jogador já enviou
  html += "jogador2.innerHTML = \"O jogador 2 fez o envio.\";";
  html += "}";
  //ao clicar no botão para ver o resultado, é feito o cálculo para descobrir se o valor é ímpar ou par
  html += "function clicar() {";
  //guarda o valor 1
  html += "var num1 = document.querySelector(\".num1\").value;";
   //guarda o valor 2
  html += "var num2 = document.querySelector(\".num2\").value;";
  //operação de soma e uso do parseInt para evitar concatenação
  html += "var resultado = parseInt(num1) + parseInt(num2);";
  //printa o resultado no html na div vazia que recebe o valor printado
  html += "document.querySelector(\".resultado\").innerHTML = resultado;";
  //guarda mensagem de erro quando os valores do input são vazios
  html += "var erro = \"Atenção! Os valores não são válidos.\";";
  //guarda mensagem se o jogador 1 ganhou
  html += "var ganhador1 = \"Parabéns! O ganhador é o jogador 1.\";";
  //guarda mensagem se o jogador 2 ganhou
  html += "var ganhador2 = \"Parabéns! O ganhador é o jogador 2.\";";
  //condição matemática para descobrir se o resultado é ímpar ou par
  html += "if (resultado % 2 == 0)";
  //printa no p vazio
  html += "document.querySelector(\".ganhador\").innerHTML = ganhador2;";
  html += "else";
  //printa no p vazio
  html += "document.querySelector(\".ganhador\").innerHTML = ganhador1;";
  //se o input tiver um tamanho menor que 1(caractere), ou seja, esteja vazio, retornará erro
  html += "if (document.getElementById(\"campo1\").value.length < 1 && document.getElementById(\"campo2\").value.length < 1)";
  //retorna erro no p vazio
  html += "document.querySelector(\".ganhador\").innerHTML = erro;";
  html += "}";
  html += "</script>";
  html += "</body>";
  html += "</html>";
    server.send(200, "text/html", html);
  }
  //liga e desliga Led após refresh da página
  void handleOn(){
    digitalWrite(led_azul, HIGH);
    delay(5000);
    digitalWrite(led_azul, LOW);
    handleRoot();
  }

  //acesso ao server
  void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  //requisição http get e post para acessar server
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
void loop() {
  server.handleClient();
  delay(2);
}