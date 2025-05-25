#include "ControllerHtml.h"
#include <Arduino.h>

const char *INDEX_HTML PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Otto控制面板</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
            margin: 0;
            background-color: #f0f0f0;
            padding: 20px;
        }
        .control-panel {
            text-align: center;
            background: white;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
            width: 100%;
            max-width: 500px;
        }
        .button-grid {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 10px;
            margin: 20px 0;
        }
        .numpad-grid {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 10px;
            margin: 20px 0;
        }
        button {
            padding: 15px;
            font-size: 18px;
            border: none;
            border-radius: 5px;
            background-color: #4CAF50;
            color: white;
            cursor: pointer;
            transition: all 0.3s ease;
            user-select: none;
            -webkit-tap-highlight-color: transparent;
        }
        button:hover {
            background-color: #45a049;
            transform: scale(1.05);
        }
        button:active {
            transform: scale(0.95);
        }
        .empty {
            visibility: hidden;
        }
        .numpad-button {
            background-color: #2196F3;
        }
        .numpad-button:hover {
            background-color: #1976D2;
        }
        .section-title {
            color: #333;
            margin: 30px 0 15px;
            font-size: 1.2em;
            font-weight: bold;
        }
        .controls-container {
            background-color: #f8f8f8;
            padding: 15px;
            border-radius: 8px;
            margin: 10px 0;
        }
        .status {
            margin-top: 10px;
            padding: 10px;
            border-radius: 5px;
            display: none;
        }
        .status.success {
            background-color: #dff0d8;
            color: #3c763d;
            display: block;
        }
        .status.error {
            background-color: #f2dede;
            color: #a94442;
            display: block;
        }
    </style>
</head>
<body>
    <div class="control-panel">
        <h1>Otto机器人控制</h1>
        <div id="status" class="status"></div>
        
        <div class="controls-container">
            <div class="section-title">方向控制</div>
            <div class="button-grid">
                <div class="empty"></div>
                <button onclick="handleCommand(this, 'forward')">前进</button>
                <div class="empty"></div>
                <button onclick="handleCommand(this, 'left')">左转</button>
                <button onclick="handleCommand(this, 'stop')">停止</button>
                <button onclick="handleCommand(this, 'right')">右转</button>
                <div class="empty"></div>
                <button onclick="handleCommand(this, 'backward')">后退</button>
                <div class="empty"></div>
            </div>
        </div>

        <div class="controls-container">
            <div class="section-title">数字键盘</div>
            <div class="numpad-grid">
                <button class="numpad-button" onclick="handleCommand(this, 'num1')">1</button>
                <button class="numpad-button" onclick="handleCommand(this, 'num2')">2</button>
                <button class="numpad-button" onclick="handleCommand(this, 'num3')">3</button>
                <button class="numpad-button" onclick="handleCommand(this, 'num4')">4</button>
                <button class="numpad-button" onclick="handleCommand(this, 'num5')">5</button>
                <button class="numpad-button" onclick="handleCommand(this, 'num6')">6</button>
                <button class="numpad-button" onclick="handleCommand(this, 'num7')">7</button>
                <button class="numpad-button" onclick="handleCommand(this, 'num8')">8</button>
                <button class="numpad-button" onclick="handleCommand(this, 'num9')">9</button>
            </div>
        </div>
    </div>

    <script>
        function showStatus(message, isError = false) {
            const status = document.getElementById('status');
            status.textContent = message;
            status.className = 'status ' + (isError ? 'error' : 'success');
            setTimeout(() => {
                status.className = 'status';
            }, 2000);
        }

        function handleCommand(button, command) {
            const originalColor = button.style.backgroundColor;
            button.style.backgroundColor = '#666';

            fetch('/' + command)
                .then(response => {
                    if (!response.ok) {
                        throw new Error('网络请求失败');
                    }
                    return response.text();
                })
                .then(data => {
                    console.log('成功:', data);
                    showStatus('命令已发送');
                    setTimeout(() => {
                        button.style.backgroundColor = button.classList.contains('numpad-button') ? '#2196F3' : '#4CAF50';
                    }, 200);
                })
                .catch(error => {
                    console.error('错误:', error);
                    showStatus('发送命令失败: ' + error.message, true);
                    setTimeout(() => {
                        button.style.backgroundColor = button.classList.contains('numpad-button') ? '#2196F3' : '#4CAF50';
                    }, 200);
                });
        }

        // 添加键盘事件支持
        document.addEventListener('keydown', function(event) {
            const key = event.key.toLowerCase();
            const keyMap = {
                'arrowup': 'forward',
                'arrowdown': 'backward',
                'arrowleft': 'left',
                'arrowright': 'right',
                ' ': 'stop',
                '1': 'num1',
                '2': 'num2',
                '3': 'num3',
                '4': 'num4',
                '5': 'num5',
                '6': 'num6',
                '7': 'num7',
                '8': 'num8',
                '9': 'num9'
            };

            if (key in keyMap) {
                event.preventDefault();
                const command = keyMap[key];
                const button = document.querySelector(`button[onclick*="${command}"]`);
                if (button) {
                    handleCommand(button, command);
                }
            }
        });
    </script>
</body>
</html>
)rawliteral";