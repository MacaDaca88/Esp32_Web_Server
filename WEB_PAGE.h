void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html lang="en">
      <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Home Main Control</title>
        <style>
          body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin: 0;
            padding: 0;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            //min-height: 100vh;
            background-color: #f0f0f0;
          }

          h1 {
            font-size: 2.5vw;
            margin: 2% 0;
          }

          .button {
            border: none;
            color: white;
            padding: 15px 20px;
            font-size: 1.2rem;
            margin: 10px;
            cursor: pointer;
            border-radius: 50%;
            transition: background-color 0.3s ease;
          }

          .green {
            background-color: green;
          }

          .red {
            background-color: red;
          }

          .Serialbox {
            border: 1px solid #ccc;
            padding: 20px;
            margin: 20px;
            border-radius: 10px;
            height: 20vh;
            overflow-y: auto;
            width: 90%;
            max-width: 800px;
            background-color: #ffffff;
          }

          .Ledbox {
            border: 2px solid #ccc;
            padding: 10px;
            margin: 10px;
            border-radius: 10px;
            width: 25%;
            max-width: 300px;
            font-size: 1rem;
            background-color: #ffffff;
          }

          .Redbox {
            border: 2px solid #ccc;
            padding: 10px;
            margin: 10px;
            border-radius: 10px;
            width: 33%;
            max-width: 300px;
            font-size: 1rem;
            background-color: red;
          }
          .Greenbox {
            border: 2px solid #ccc;
            padding: 10px;
            margin: 10px;
            border-radius: 10px;
            width: 33%;
            max-width: 300px;
            font-size: 1rem;
            background-color: green;
          }
          .Bluebox {
            border: 2px solid #ccc;
            padding: 10px;
            margin: 10px;
            border-radius: 10px;
            width: 33%;
            max-width: 300px;
            font-size: 1rem;
            background-color: blue;
          }
          
          @media (max-width: 768px) {
            h1 {
              font-size: 5vw;
            }

            .button {
              padding: 10px 15px;
              font-size: 1rem;
            }

            .Serialbox {
              height: 30vh;
            }

            .Ledbox {
              width: 80%;
            }
          }

          @media (min-width: 2560px) { /* For 4K screens */
            h1 {
              font-size: 2vw;
            }

            .button {
              padding: 20px 25px;
              font-size: 1.5rem;
            }

            .Serialbox {
              height: 25vh;
            }

            .Ledbox {
              font-size: 1.2rem;
            }
          }
        </style>
      </head>
      <body>
        <h1>Home Main Control</h1>
        <div class="Serialbox" id="serialBox"></div>
        <div class="Ledbox" id="ledStateBox">LED State will appear here...</div>
        <br>
        <button class="button green" onclick="location.href='/ledOn'">ON</button>
        <button class="button red" onclick="location.href='/ledOff'">OFF</button>
        <br>
        <div class="Redbox" id="Redbox">RED</div>
        <div class="Greenbox" id="Redbox">GREEN</div>
        <div class="Bluebox" id="Redbox">BLUE</div>

        <script>
          var serialSource = new EventSource('/serial');
          serialSource.onmessage = function(event) {
            if (event.data.trim() !== '') {
              var serialBox = document.getElementById('serialBox');
              serialBox.innerHTML += event.data + '<br>';
              serialBox.scrollTop = serialBox.scrollHeight;
            }
          };

          var ledStateSource = new EventSource('/ledState');
          ledStateSource.onmessage = function(event) {
            document.getElementById('ledStateBox').innerHTML = event.data;
          };
        </script>
      </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}
