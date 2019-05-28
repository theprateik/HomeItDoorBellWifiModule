
  //do work

var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);
connection.onopen = function () {
  connection.send('Connect ' + new Date());
};
connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};
connection.onmessage = function (e) {
  console.log('Server: ', e.data);
};
connection.onclose = function () {
  console.log('WebSocket connection closed');
};

function saveWiFiConfig() {
  var ssid = document.getElementById("txtSsid").value;
  var password = document.getElementById("txtPassword").value;
  var data = {
      type: "WiFiConfiguration",
      ssid: ssid,
      password: password
  }
  window.location = "#savingModal";
  connection.send(JSON.stringify(data));
}