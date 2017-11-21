/*
* Part: Graphical User Interface
* Module: Websocket Client
* Author: zxc479773533@github.com
* LICENSE: GNU GENERAL PUBLIC LICENSE V3.0
*/

// creat websocket
var ws = new WebSocket('ws://localhost:12345');

// event when the websocket is opened
ws.onopen = function (evt) {
    console.log('Connected to server.');
}

// event when client receive a message
ws.onmessage = function (evt) {
    mainReceive(evt.data);
}

// event when error happens
ws.onerror = function (evt) {
    alert('There is something wrong with your network, please check your server.')
    console.log('Error occured.')
}

// event when the websocket is closed
ws.onclose = function (evt) {
    alert('Connection closed.');
    console.log('Connection closed.');
}

// receive data from server
function mainReceive (data) {
    console.log(data);
    data = data.replace(/\n/g, '<br/>');
    data += '<br/>'
    /*TO BE WRITE*/

    document.getElementById('console_content').innerHTML += data;
    document.getElementById('console_end').scrollIntoView();;
}

// send request to server
function mainSend () {
    
    var buffer = '';
    var ok = 1;
    
    for (let arg of arguments) {
        if (arg == '') {
            alert("请输入参数！");
            ok = 0;
            break;
        }
        else {
            buffer += arg + '\r\n';
        }
    }
    if (ok == 1) {
        console.log(buffer);
        ws.send(buffer);        
    }
}