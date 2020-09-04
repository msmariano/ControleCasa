#include "ControleCasa.h"

void enviaAlive() {

  if (!aliveRetorno) {
    log(String("ALIVE SEM RETORNO. REINICIANDO CONEXAO..."));
    client.stop();
    conectado = false;
  }
  aliveRetorno = false;
  if (conectado) {

    //log("ALIVE...");
    client.print(alive());
  }
}






String retorno(String jSon)
{
  StaticJsonDocument<1000> retJson;
  String retorno = "";
  retJson["id"] = idRetorno;
  retJson["usuario"] = usuario;
  retJson["nome"] = nomeConector;
  retJson["tipo"] = tipoIot;
  retJson["senha"]   =  senha;
  retJson["iot"]["id"] = idIot;
  if (jSon != "")
    retJson["iot"]["jSon"] = jSon;
  retJson["iot"]["name"] = nameIot;
  retJson["status"] = "RETORNO";
  serializeJson(retJson, retorno);
  return retorno + "\n";

}




String login()
{
  String retorno = "";
  doc["id"] = id;
  doc["nome"] = nomeConector;
  doc["usuario"] = usuario;
  doc["senha"]   =  senha;
  doc["iot"]["id"] = 0;
  doc["iot"]["name"] = nameIot;
  doc["status"] = "LOGIN";
  serializeJson(doc, retorno);
  //Serial.print("login json: ");
  //Serial.print(retorno);
  //log("...");
  return retorno + "\r\n";

}

String executaComando()
{
  String json = doc["iot"]["jSon"];

  log(json);

  if (json == "null")
  { log("sem comando");
    return "";
  }

  DeserializationError error = deserializeJson(com, json);
  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    log(error.c_str());
  }

  else {


    int buttonID = com[0]["buttonID"];
    String tecla    = com[0]["tecla"];
    String statusB  = com[0]["status"];
    String funcao = com[0]["funcao"];
    String btJson = com[0]["jSon"];

    Serial.printf("%d - ", buttonID);
    Serial.print(tecla + " -  ");
    log(statusB);

    if (statusB == "READ") {
      String sRet = "";
      StaticJsonDocument<1000> retRead;
      retRead["buttonID"] = 1;
      retRead["status"] = atualEstado;
      retRead["tecla"] = 1;
      retRead["funcao"] = "READ";
      serializeJson(retRead, sRet);
      return sRet;

    }

    if (statusB == "ALEATORIOON") {
      aguardandoTemporizador = false;
      acionarTemporizador = true;
      horaAtual = "";
      inicializaTemporizador();
      ativarAleatorio = true;

      String sRet = "";
      StaticJsonDocument<1000> retRead;
      StaticJsonDocument<1000> button;
      retRead["horaInicializacao"] = horaAtual;
       if(foraHorarioTimer)
        retRead["horaTemporizador"] = "Fora do horário";
      else
        retRead["horaTemporizador"] = horaTemporizador;
      retRead["horaInicioTemporizador"] = horaInicioTemporizador;
      retRead["horaFinalTemporizador"] = horaFinalTemporizador;
      retRead["duracao"] = duracao;
      serializeJson(retRead, sRet);
      
      button["buttonID"] = 1;
      button["status"] = atualEstado;
      button["tecla"] = 1;
      button["funcao"] = "ALEATORIOON";
      button["jSon"] = sRet;
      sRet = "";
      serializeJson(button, sRet);
      
      
      return sRet;
    }

    if(statusB == "ALEATORIOINFO"){
      String sRet = "";
      StaticJsonDocument<1000> retRead;
      StaticJsonDocument<1000> button;
      retRead["horaInicializacao"] = horaAtual;
      if(foraHorarioTimer)
        retRead["horaTemporizador"] = "Fora do horário";
      else
        retRead["horaTemporizador"] = horaTemporizador;
      retRead["horaInicioTemporizador"] = horaInicioTemporizador;
      retRead["horaFinalTemporizador"] = horaFinalTemporizador;
      retRead["duracao"] = duracao;
      retRead["ativarAleatorio"] = ativarAleatorio;
      serializeJson(retRead, sRet);
      
      button["buttonID"] = 1;
      button["status"] = atualEstado;
      button["tecla"] = 1;
      button["funcao"] = "ALEATORIOINFO";
      button["jSon"] = sRet;
      sRet = "";
      serializeJson(button, sRet);

      
      return sRet;

    }

    if (statusB == "ALEATORIOOFF") {
      
      String sRet = "";
      StaticJsonDocument<1000> retRead;
      StaticJsonDocument<1000> button;
      retRead["horaInicializacao"] = horaAtual;
      retRead["horaTemporizador"] = horaTemporizador;
      retRead["horaInicioTemporizador"] = horaInicioTemporizador;
      retRead["horaFinalTemporizador"] = horaFinalTemporizador;
      retRead["duracao"] = duracao;
      serializeJson(retRead, sRet);
      
      button["buttonID"] = 1;
      button["status"] = atualEstado;
      button["tecla"] = 1;
      button["funcao"] = "ALEATORIOOFF";
      button["jSon"] = sRet;
      sRet = "";
      serializeJson(button, sRet);

      ativarAleatorio = false;
      return sRet;

    }

    
    if (statusB == "OUT")
    {
      StaticJsonDocument<1000> button;
      String sRet = "";

      if (tecla == "ON")
      {
        ultimoAcionador = 0;
        log("Ligando...");
        digitalWrite(D3, LOW);
        atualEstado = "ON";
      }
      else if (tecla == "OFF")
      {
        ultimoAcionador = 2;
        log("Desligando...");
        digitalWrite(D3, HIGH);
        atualEstado = "OFF";
      }

      button["buttonID"] = 1;
      button["status"] = atualEstado;
      button["tecla"] = 1;
      button["funcao"] = "ACIONARBOTAO";
      button["jSon"] = sRet;
      sRet = "";
      serializeJson(button, sRet);
      return sRet;

    }
    
  }
  return "";
}


/*String retornoHoraData() {
  timeClient.update();
  return timeClient.getFormattedTime();
}*/

String alive()
{
  String retorno = "";
  doc["id"] = id;
  doc["usuario"] = usuario;
  doc["nome"] = nomeConector;
  doc["tipo"] = tipoIot;
  doc["senha"]   =  senha;
  doc["iot"]["id"] = idIot;
  doc["iot"]["name"] = nameIot;
  doc["status"] = "ALIVE";
  serializeJson(doc, retorno);
  return retorno + "\r\n";

}

void fInterruptor() {
  //Serial.println("Lendo Interruptor");

  //Serial.printf("Lendo portas : %d %d %d %d %d %d %d %d", digitalRead(0),
  //  digitalRead(1), digitalRead(2), digitalRead(4), digitalRead(5), digitalRead(6), digitalRead(7), digitalRead(8));


  //Serial.println("");

  if ( digitalRead(2) != interruptor ) {
    interruptor = digitalRead(2);
    if (atualEstado == "ON")
    {
      ultimoAcionador = 2;
      log("Desligando...");
      digitalWrite(D3, HIGH);
      atualEstado = "OFF";
    }
    else if (atualEstado == "OFF")
    {
      ultimoAcionador = 1;
      log("ligando...");
      digitalWrite(D3, LOW);
      atualEstado = "ON";
    }
  }
  delay(1);
}

void desativaMotorBombaPiscina(){
  if(ultimoAcionador == 2)
    digitalWrite(D3, HIGH);
}
void ativaMotorBombaPiscina(){
  digitalWrite(D3, LOW);
}

void fAleatorio() {

  //compilacao para a piscina
  /*if(  bLigarPiscina && (calculoSegundo(retornoHoraData()) > calculoSegundo("10:00:00")
      && calculoSegundo(retornoHoraData()) < calculoSegundo("10:15:00")) ){
      ativaMotorBombaPiscina(); 
      bLigarPiscina = false; 
      bdesLigarPiscina = true;   
  }
  else if(bdesLigarPiscina && (calculoSegundo(retornoHoraData()) > calculoSegundo("10:15:00"))){
       bLigarPiscina = true;
       bdesLigarPiscina = false;
       desativaMotorBombaPiscina();
  }

  if( bLigarPiscina &&  ( calculoSegundo(retornoHoraData()) > calculoSegundo("17:00:00")
      && calculoSegundo(retornoHoraData()) < calculoSegundo("17:15:00") ) ){
     ativaMotorBombaPiscina(); 
  }
  else if(bdesLigarPiscina && (calculoSegundo(retornoHoraData()) > calculoSegundo("17:15:00"))){
       bLigarPiscina = true;
       bdesLigarPiscina = false;
       desativaMotorBombaPiscina();
  }*/


  //////////////////////////////
  if( calculoSegundo(retornoHoraData()) < calculoSegundo("19:00:00")
      && calculoSegundo(retornoHoraData()) > calculoSegundo("05:00:00")  ){
       foraHorarioTimer = true; 
       return ;
  }
  else
  {
    foraHorarioTimer  = false;
  }
  


  if (ativarAleatorio) {

    

    inicializaTemporizador();

    if (acionarTemporizador) {
      if (!aguardandoTemporizador && horaInicioTemporizador < calculoSegundo(retornoHoraData())) {
        Serial.println("Ativando temporizador as " + retornoHoraData());
        aguardandoTemporizador = true;
        //ultimoAcionador = 2;
        digitalWrite(D3, LOW);
      }
      if (aguardandoTemporizador && horaFinalTemporizador < calculoSegundo(retornoHoraData()))
      {
        acionarTemporizador = false;
        aguardandoTemporizador = false;
        Serial.println("Desativando temporizador as " + retornoHoraData());
        if(ultimoAcionador == 2)
          digitalWrite(D3, HIGH);

      }
    }
  }
}

void reinicializarIOT() {
  if ( horaAtualResetar !=  retornoHoraData().substring(0, 2) ) {
    horaAtualResetar = retornoHoraData().substring(0, 2);
    if (horaAtualResetarInicializar) {

    }
    horaAtualResetarInicializar = true;
  }
}

void inicializaTemporizador() {
  minutoAletorio = 0;
  dataHora = retornoHoraData();

  if (!aguardandoTemporizador && horaAtual != dataHora.substring(0, 2) ) {
    horaTemporizador = "";
    horaAtual = dataHora.substring(0, 2);
    acionarTemporizador = true;
    Serial.println( "Hora de inicialização: " + dataHora);
    horaAtual =  dataHora.substring(0, 2);
    minutoAtual = dataHora.substring(3, 5);
    segundoAtual = dataHora.substring(6, 8);
    minutoAletorio = random(60);
    if (minutoAletorio < minutoAtual.toInt()) {
      minutoAletorio = minutoAletorio + minutoAtual.toInt();
      if(minutoAletorio>59){
        minutoAletorio = 59;
      }
    }


    if (minutoAletorio < 10)
      horaTemporizador = horaAtual + ":0" + String(minutoAletorio) ;
    else
      horaTemporizador = horaAtual + ":" + String(minutoAletorio) ;

    duracao = random(13) + 2;

    Serial.println( "Hora de acionamento do temporizador: " + horaTemporizador);
    Serial.println( "Duracao:" + String(duracao));

    horaInicioTemporizador = calculoSegundo(horaTemporizador + ":00");
    horaFinalTemporizador  = horaInicioTemporizador + duracao * 60;
    Serial.println( "Posição do segundo do dia do inicio da temporização: " + String(horaInicioTemporizador));
    Serial.println( "Posição do segundo do dia do final da temporização: " + String(horaFinalTemporizador));

  }
}

void setup()
{
  

  
  pinMode(D3, OUTPUT);

  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);

  randomSeed(analogRead(0));

  digitalWrite(D3, LOW);
  Serial.begin(115200);

  delay(5000);
  Serial.write(12);
  Serial.println();

  Serial.print("Connecting to " + ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  
  myThread.onRun(enviaAlive);
  myThread.setInterval(10000);
}


void loop()
{
  fInterruptor();
  fAleatorio();


  Serial.print("\n" + retornoHoraData() + " [Connecting to " + server + " ... ");
  conectado = false;
  if (client.connect(server, porta))
  {
    Serial.println("connected]");
    log("Logando.");
    client.print(login());

    while (client.connected())
    {
      fInterruptor();
      fAleatorio();
      //log("Conectado...Aguardando dados");
      if (myThread.shouldRun())
        myThread.run();

      if (WiFi.status() != WL_CONNECTED) {
        log("Perda conexão Wifi. Tentando recuperar");
        client.stop();
        WiFi.disconnect();
        status = WL_IDLE_STATUS;
        while ( status != WL_CONNECTED) {
          status = WiFi.begin(ssid, password);
          delay(10000);
        }
        return;
      }


      if (client.available())
      {
        //log("Disponivel...Aguardando dados");
        String line = client.readStringUntil('\n');
        if (line == "")
        {
          log("Retorno vazio");
          continue;
        }
        //log(line);
        DeserializationError error = deserializeJson(doc, line);
        if (error)
        {
          Serial.print(F("deserializeJson() failed: "));
          log(error.c_str());
        }
        else
        {




          String status = doc["status"];
          //Serial.print(retornoHoraData() + " Evento - ");
          //Serial.println(status);



          if (status == "FAIL")
          {
            log("Conexão falhou...");
            String erro = doc["erro"];
            log(erro);
            delay(5000);
            client.stop();
            return;
          }
          if (status == "CONECTADO")
          {
            String nome = doc["nome"];
            String getId = doc["id"];
            id = getId;
            //Serial.print(retornoHoraData() + " " + nome + " - ID:");
            //Serial.println(id);
            conectado = true;
            aliveRetorno = true;
            //client.print(alive());

          }
          if (status == "CONTROLLERCOMMAND")
          {
            String getIdIot = doc["iot"]["id"];
            idIot =  getIdIot;
            String jSonRetorno = "";
            String getIdRetorno = doc["id"];
            idRetorno = getIdRetorno;
            log("Executando comando");
            jSonRetorno = executaComando();
            client.print(retorno(jSonRetorno));
          }
        }
      }
      else
      {
        //log("Sem dados...");
        delay(1000);
      }
    }
    client.stop();
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(5000);
}





