void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html lang="en">
      <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Home Control</title>
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
  background-image: url('https://wallpapers.com/images/featured-full/ambient-background-b6kd5x4jm5nlr2r2.jpg');
  background-size: cover;  /* Adjusts the image to cover the entire background */
  background-position: center; /* Centers the image */
  background-repeat: no-repeat; /* Prevents the image from repeating */
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
            width: 15%;
            max-width: 300px;
            font-size: 1rem;
            background-color: #ffffff;
          }
          .ColorInputContainer {
            display: flex;
            flex-direction: row;
            align-items: center;
            gap: 20px;
            margin: 20px 0;
          }
          .Colorbox {
            border: 2px solid #ccc;
            padding: 10px;
            border-radius: 10px;
            width: 80%;
            max-width: 300px;
            font-size: 1rem;
            display: flex;
            flex-direction: column;
            align-items: center;
            background-color: #f0f0f0;
          }
          input[type='number'] {
            width: 60px;
            margin-top: 10px;
            text-align: center;
          }
          input[type='range'] {
            width: 80%;
          }
          .send-button {
            margin-top: 20px;
            padding: 10px 20px;
            font-size: 1.2rem;
            cursor: pointer;
            border-radius: 5px;
            background-color: #007bff;
            color: white;
            border: none;
            transition: background-color 0.3s ease;
          }
          .send-button:hover {
            background-color: #0056b3;
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
          @media (min-width: 2560px) {
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
        <div class="ColorInputContainer">
          <div class="Colorbox" style="background-color: rgba(255, 0, 0, 0.6);">
            <label for="redValue">RED</label>
            <input type="range" id="redSlider" min="0" max="255" value="0" oninput="updateValue('redSlider', 'redValue')">
            <input type="number" id="redValue" min="0" max="255" value="0" oninput="updateSlider('redValue', 'redSlider')">
          </div>
          <div class="Colorbox" style="background-color: rgba(0, 255, 0, 0.6);">
            <label for="greenValue">GREEN</label>
            <input type="range" id="greenSlider" min="0" max="255" value="0" oninput="updateValue('greenSlider', 'greenValue')">
            <input type="number" id="greenValue" min="0" max="255" value="0" oninput="updateSlider('greenValue', 'greenSlider')">
          </div>
          <div class="Colorbox" style="background-color: rgba(0, 0, 255, 0.6);">
            <label for="blueValue">BLUE</label>
            <input type="range" id="blueSlider" min="0" max="255" value="0" oninput="updateValue('blueSlider', 'blueValue')">
            <input type="number" id="blueValue" min="0" max="255" value="0" oninput="updateSlider('blueValue', 'blueSlider')">
          </div>
        </div>
        <button class="send-button" onclick="sendRGB()">Send</button>

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

          function updateValue(sliderId, inputId) {
            document.getElementById(inputId).value = document.getElementById(sliderId).value;
          }

          function updateSlider(inputId, sliderId) {
            document.getElementById(sliderId).value = document.getElementById(inputId).value;
          }

          function sendRGB() {
            var red = document.getElementById('redValue').value;
            var green = document.getElementById('greenValue').value;
            var blue = document.getElementById('blueValue').value;
            var rgbValues = `${red},${green},${blue}`;
            console.log('Sending RGB values:', rgbValues);
            fetch(`/setRGB?values=${rgbValues}`)
              .then(response => response.text())
              .then(data => console.log('Response from ESP32:', data))
              .catch(error => console.error('Error sending RGB values:', error));
          }
        </script>
      </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}
