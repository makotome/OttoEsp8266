#include "ControllerHtml.h"
#include <Arduino.h>

const char *INDEX_HTML PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>毛毛小七机器人遥控器</title>
    <style>
        :root {
            --primary-color: #FF4081;
            --secondary-color: #3F51B5;
            --success-color: #4CAF50;
            --movement-color: #E91E63;
            --action-color: #9C27B0;
            --numpad-color: #2196F3;
        }

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
            border-radius: 20px;
            box-shadow: 0 0 20px rgba(0, 0, 0, 0.2);
            width: 100%;
            max-width: 600px;
        }

        .ip-container {
            margin: 20px 0;
            padding: 15px;
            background-color: #f8f8f8;
            border-radius: 10px;
        }

        .ip-input {
            padding: 10px;
            width: 200px;
            border: 2px solid var(--secondary-color);
            border-radius: 5px;
            margin-right: 10px;
        }

        .save-ip {
            padding: 10px 20px;
            background-color: var(--secondary-color);
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }

        .button-grid {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 15px;
            margin: 20px 0;
        }

        .action-grid {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 15px;
            margin: 20px 0;
        }

        .numpad-grid {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 15px;
            margin: 20px 0;
        }

        button {
            padding: 15px;
            font-size: 16px;
            border: none;
            border-radius: 15px;
            color: white;
            cursor: pointer;
            transition: all 0.3s ease;
            user-select: none;
            -webkit-tap-highlight-color: transparent;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }

        .movement-button {
            background-color: var(--movement-color);
        }

        .action-button {
            background-color: var(--action-color);
        }

        .numpad-button {
            background-color: var(--numpad-color);
        }

        button:hover {
            transform: translateY(-2px);
            box-shadow: 0 6px 8px rgba(0, 0, 0, 0.2);
        }

        button:active {
            transform: translateY(1px);
        }

        .empty {
            visibility: hidden;
        }

        .section-title {
            color: #333;
            margin: 30px 0 15px;
            font-size: 1.3em;
            font-weight: bold;
            text-transform: uppercase;
        }

        .controls-container {
            background-color: #f8f8f8;
            padding: 20px;
            border-radius: 15px;
            margin: 15px 0;
        }

        .status {
            margin-top: 10px;
            padding: 10px;
            border-radius: 10px;
            display: none;
            font-weight: bold;
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

        .nav-button {
            background-color: var(--secondary-color);
            margin: 10px 0;
            width: 100%;
        }
    </style>
</head>

<body>
    <div class="control-panel">
        <h1>Otto机器人遥控器</h1>
        <div class="ip-container">
            <input type="text" id="ipAddress" class="ip-input" placeholder="输入机器人IP地址">
            <button onclick="saveIP()" class="save-ip">保存IP</button>
        </div>
        <div id="status" class="status"></div>

        <button onclick="navigateToProgramming()" class="nav-button">进入编程界面</button>

        <div class="controls-container">
            <div class="section-title">方向控制</div>
            <div class="button-grid">
                <div class="empty"></div>
                <button class="movement-button" onclick="handleCommand(this, 'forward')">前进</button>
                <div class="empty"></div>
                <button class="movement-button" onclick="handleCommand(this, 'left')">左转</button>
                <button class="movement-button" onclick="handleCommand(this, 'stop')">停止</button>
                <button class="movement-button" onclick="handleCommand(this, 'right')">右转</button>
                <div class="empty"></div>
                <button class="movement-button" onclick="handleCommand(this, 'backward')">后退</button>
                <div class="empty"></div>
            </div>
        </div>

        <div class="controls-container">
            <div class="section-title">动作控制</div>
            <div class="action-grid">
                <button class="action-button" onclick="handleCommand(this, 'sing')">唱歌</button>
                <button class="action-button" onclick="handleCommand(this, 'dance')">跳舞</button>
                <button class="action-button" onclick="handleCommand(this, 'emotion')">表情</button>
                <button class="action-button" onclick="handleCommand(this, 'jump')">跳跃</button>
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
        let baseUrl = '';

        // 从localStorage加载保存的IP
        window.onload = function () {
            const savedIP = localStorage.getItem('robotIP');
            if (savedIP) {
                document.getElementById('ipAddress').value = savedIP;
                baseUrl = `http://${savedIP}`;
            }
        }

        function saveIP() {
            const ip = document.getElementById('ipAddress').value.trim();
            if (ip) {
                localStorage.setItem('robotIP', ip);
                baseUrl = `http://${ip}`;
                showStatus('IP地址已保存');
            } else {
                showStatus('请输入有效的IP地址', true);
            }
        }

        function showStatus(message, isError = false) {
            const status = document.getElementById('status');
            status.textContent = message;
            status.className = 'status ' + (isError ? 'error' : 'success');
            setTimeout(() => {
                status.className = 'status';
            }, 2000);
        }

        function handleCommand(button, command) {
            if (!baseUrl) {
                showStatus('请先设置IP地址', true);
                return;
            }

            const originalColor = button.style.backgroundColor;
            button.style.opacity = '0.7';

            // 创建请求数据
            const data = {
                command: command
            };

            fetch(`${baseUrl}/command`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(data)
            })
                .then(response => {
                    if (!response.ok) {
                        throw new Error('网络请求失败');
                    }
                    return response.json();
                })
                .then(data => {
                    console.log('成功:', data);
                    showStatus(data.message || '命令已发送');
                    setTimeout(() => {
                        button.style.opacity = '1';
                    }, 200);
                })
                .catch(error => {
                    console.error('错误:', error);
                    showStatus('发送命令失败: ' + error.message, true);
                    setTimeout(() => {
                        button.style.opacity = '1';
                    }, 200);
                });
        }

        function navigateToProgramming() {
            if (!baseUrl) {
                showStatus('请先设置IP地址', true);
                return;
            }
            window.location.href = `${baseUrl}/programming`;
        }

        // 添加键盘事件支持
        document.addEventListener('keydown', function (event) {
            const key = event.key.toLowerCase();
            const keyMap = {
                'arrowup': 'forward',
                'arrowdown': 'backward',
                'arrowleft': 'left',
                'arrowright': 'right',
                ' ': 'stop',
                's': 'sing',
                'd': 'dance',
                'e': 'emotion',
                'j': 'jump',
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

const char *PROGRAME_HTML PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>毛毛小七机器人编程</title>
    <style>
        body {
            margin: 0;
            padding: 20px;
            font-family: Arial, sans-serif;
            background-color: #f0f0f0;
            display: flex;
            min-height: 100vh;
        }

        .ip-settings {
            margin-bottom: 20px;
            padding: 10px;
            background-color: #f8f8f8;
            border-radius: 5px;
        }

        .ip-settings input {
            padding: 5px;
            margin: 0 10px;
            width: 150px;
        }

        /* 在 style 标签中添加或修改以下样式 */
        .ip-settings .control-button {
            background-color: #2196F3;
            /* 使用蓝色 */
            padding: 5px 15px;
            /* 调整大小 */
            margin-left: 10px;
            /* 添加间距 */
        }

        .ip-settings .control-button:hover {
            background-color: #1976D2;
            /* 鼠标悬停时的颜色 */
        }

        .blocks-panel {
            width: 300px;
            background: white;
            border-radius: 10px;
            padding: 20px;
            margin-right: 20px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            overflow-y: auto;
            max-height: calc(100vh - 40px);
        }

        .program-panel {
            flex: 1;
            background: white;
            border-radius: 10px;
            padding: 20px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            display: flex;
            flex-direction: column;
        }

        .block-category {
            margin-bottom: 20px;
        }

        .category-title {
            font-weight: bold;
            color: #333;
            margin-bottom: 10px;
            padding-bottom: 5px;
            border-bottom: 2px solid #eee;
        }

        .block {
            padding: 10px;
            margin: 5px 0;
            border-radius: 5px;
            cursor: move;
            user-select: none;
            color: white;
            display: flex;
            align-items: center;
        }

        .block input {
            width: 50px;
            margin-left: 10px;
            padding: 2px 5px;
        }

        .movement-block {
            background-color: #4CAF50;
        }

        .action-block {
            background-color: #2196F3;
        }

        .song-block {
            background-color: #9C27B0;
        }

        .song-block select {
            margin-left: 10px;
            padding: 2px 5px;
            width: 100px;
        }

        .program-item.song {
            background-color: #F3E5F5;
        }

        .program-area {
            flex: 1;
            border: 2px dashed #ccc;
            border-radius: 8px;
            padding: 20px;
            min-height: 300px;
            margin-bottom: 20px;
        }

        .program-area.dragover {
            border-color: #2196F3;
            background-color: #E3F2FD;
        }

        .program-item {
            display: flex;
            align-items: center;
            margin: 5px 0;
            padding: 10px;
            background-color: #f8f8f8;
            border-radius: 5px;
            cursor: move;
        }

        .program-item input {
            width: 60px;
            margin: 0 10px;
        }

        .program-controls {
            display: flex;
            gap: 10px;
            justify-content: center;
        }

        .control-button {
            padding: 10px 20px;
            border: none;
            border-radius: 5px;
            color: white;
            cursor: pointer;
            font-size: 16px;
        }

        .start-button {
            background-color: #4CAF50;
        }

        .clear-button {
            background-color: #f44336;
        }

        .back-button {
            background-color: #607D8B;
        }

        .placeholder {
            color: #999;
            text-align: center;
            padding: 20px;
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
    <div class="blocks-panel">
        <div class="ip-settings">
            <label for="ipHost">服务器地址：</label>
            <input type="text" id="ipHost" value="192.168.0.107">
            <button onclick="saveIP()" class="control-button">保存</button>
        </div>
        <h2>编程区域</h2>
        <div class="block-category">
            <div class="category-title">移动指令</div>
            <div class="block movement-block" draggable="true" data-command="forward">
                前进
                <input type="number" min="1" max="10" value="2">步
            </div>
            <div class="block movement-block" draggable="true" data-command="backward">
                后退
                <input type="number" min="1" max="10" value="2">步
            </div>
            <div class="block movement-block" draggable="true" data-command="left">
                左转
                <input type="number" min="1" max="10" value="2">步
            </div>
            <div class="block movement-block" draggable="true" data-command="right">
                右转
                <input type="number" min="1" max="10" value="2">步
            </div>
            <div class="block movement-block" draggable="true" data-command="stop">
                停止
                <input type="number" min="1" max="10" value="2">步
            </div>
        </div>

        <div class="block-category">
            <div class="category-title">动作指令</div>
            <div class="block action-block" draggable="true" data-command="leftBend">
                左弯腿
                <input type="number" min="1" max="10" value="2">次
            </div>
            <div class="block action-block" draggable="true" data-command="rightBend">
                右弯腿
                <input type="number" min="1" max="10" value="2">次
            </div>
            <div class="block action-block" draggable="true" data-command="leftShake">
                左抖脚
                <input type="number" min="1" max="10" value="2">次
            </div>
            <div class="block action-block" draggable="true" data-command="rightShake">
                右抖脚
                <input type="number" min="1" max="10" value="2">次
            </div>
            <div class="block action-block" draggable="true" data-command="leftSpaceWalk">
                左太空步
                <input type="number" min="1" max="10" value="2">次
            </div>
            <div class="block action-block" draggable="true" data-command="rightSpaceWalk">
                右太空步
                <input type="number" min="1" max="10" value="2">次
            </div>
            <div class="block action-block" draggable="true" data-command="leftFlap">
                向左扇动
                <input type="number" min="1" max="10" value="2">次
            </div>
            <div class="block action-block" draggable="true" data-command="rightFlap">
                向右扇动
                <input type="number" min="1" max="10" value="2">次
            </div>
            <!-- 更多动作指令 -->
        </div>
        <div class="block-category">
            <div class="category-title">唱歌指令</div>
            <div class="block song-block" draggable="true" data-command="sing">
                唱歌
                <select class="song-select">
                    <option value="0">连接声</option>
                    <option value="1">断开声</option>
                    <option value="2">按钮声</option>
                    <option value="3">模式1</option>
                    <option value="4">模式2</option>
                    <option value="5">模式3</option>
                    <option value="6">惊讶</option>
                    <option value="7">哦呜1</option>
                    <option value="8">哦呜2</option>
                    <option value="9">撒娇</option>
                    <option value="10">睡觉</option>
                    <option value="11">开心</option>
                    <option value="12">超开心</option>
                    <option value="13">短开心</option>
                    <option value="14">悲伤</option>
                    <option value="15">困惑</option>
                    <option value="16">放屁1</option>
                    <option value="17">放屁2</option>
                    <option value="18">放屁3</option>
                </select>
            </div>
        </div>
    </div>

    <div class="program-panel">
        <h2>编程区域</h2>
        <div id="status" class="status"></div>
        <div id="program-area" class="program-area">
            <div class="placeholder">拖动左侧积木块到这里开始编程</div>
        </div>
        <div class="program-controls">
            <button onclick="location.href='/'" class="control-button back-button">返回控制面板</button>
            <button onclick="startProgram()" class="control-button start-button">开始执行</button>
            <button onclick="clearProgram()" class="control-button clear-button">清除</button>
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

        // 添加 IP 存储和获取函数
        function saveIP() {
            const ip = document.getElementById('ipHost').value;
            localStorage.setItem('serverIP', ip);
            showStatus('IP地址已保存');
        }

        function getServerIP() {
            return localStorage.getItem('serverIP') || '192.168.0.107';
        }

        function initDragAndDrop() {
            const blocks = document.querySelectorAll('.block');
            const programArea = document.getElementById('program-area');

            blocks.forEach(block => {
                block.addEventListener('dragstart', handleDragStart);
                // 修改这里的事件处理
                const input = block.querySelector('input');
                const select = block.querySelector('select');

                if (input) {
                    input.addEventListener('mousedown', e => {
                        e.stopPropagation();
                    });
                }

                if (select) {
                    select.addEventListener('mousedown', e => {
                        e.stopPropagation();
                    });
                }
            });

            programArea.addEventListener('dragover', handleDragOver);
            programArea.addEventListener('drop', handleDrop);
            programArea.addEventListener('dragenter', handleDragEnter);
            programArea.addEventListener('dragleave', handleDragLeave);
        }

        // 修改拖拽处理
        function handleDragStart(e) {
            try {
                const block = e.target;
                const data = {
                    command: block.dataset.command,
                    text: block.childNodes[0].textContent.trim(),
                    type: block.classList.contains('song-block') ? 'song' :
                        block.classList.contains('movement-block') ? 'movement' : 'action'
                };

                if (data.type === 'song') {
                    const select = block.querySelector('select');
                    data.songValue = select.value;
                    data.songText = select.options[select.selectedIndex].text;
                } else {
                    const input = block.querySelector('input');
                    data.steps = input ? input.value : '2';
                }

                e.dataTransfer.setData('text/plain', JSON.stringify(data));
                console.log('拖动开始:', data); // 添加调试日志
            } catch (error) {
                console.error('拖动处理失败:', error);
            }
        }

        function handleDragOver(e) {
            e.preventDefault();
        }

        function handleDragEnter(e) {
            // 修改获取程序区域的方法
            const programArea = e.target.closest('.program-area');
            if (programArea) {
                programArea.classList.add('dragover');
            }
        }

        function handleDragLeave(e) {
            // 修改获取程序区域的方法
            const programArea = e.target.closest('.program-area');
            if (programArea) {
                programArea.classList.remove('dragover');
            }
        }

        function handleDrop(e) {
            e.preventDefault();
            // 修改获取程序区域的方法
            let programArea = e.target;
            if (!programArea.classList.contains('program-area')) {
                programArea = programArea.closest('.program-area');
            }

            if (!programArea) return;

            programArea.classList.remove('dragover');

            try {
                const data = JSON.parse(e.dataTransfer.getData('text/plain'));
                const item = createProgramItem(data);

                if (programArea.querySelector('.placeholder')) {
                    programArea.innerHTML = '';
                }
                programArea.appendChild(item);
            } catch (error) {
                console.error('拖放数据解析失败:', error);
            }
        }

        // 修改创建程序项函数
        function createProgramItem(data) {
            const div = document.createElement('div');
            div.className = `program-item ${data.type}`;

            if (data.type === 'song') {
                div.innerHTML = `
            <span>${data.text}</span>
            <select class="song-select">
                ${document.querySelector('.song-select').innerHTML}
            </select>
            <button onclick="removeItem(this)" class="control-button clear-button">删除</button>
        `;
                div.querySelector('select').value = data.songValue;
            } else {
                div.innerHTML = `
            <span>${data.text}</span>
            <input type="number" min="1" max="10" value="${data.steps}">
            <span>步</span>
            <button onclick="removeItem(this)" class="control-button clear-button">删除</button>
        `;
            }

            div.dataset.command = data.command;
            div.draggable = true;
            return div;
        }

        function removeItem(button) {
            const item = button.parentElement;
            item.remove();

            const programArea = document.getElementById('program-area');
            if (!programArea.children.length) {
                programArea.innerHTML = '<div class="placeholder">拖动左侧积木块到这里开始编程</div>';
            }
        }

        // 修改程序执行函数
        function startProgram() {
            const items = document.querySelectorAll('.program-item');
            const program = Array.from(items).map(item => {
                const command = item.dataset.command;
                if (item.classList.contains('song')) {
                    return {
                        command: 'sing',
                        songValue: parseInt(item.querySelector('select').value)
                    };
                } else {
                    return {
                        command: command,
                        steps: parseInt(item.querySelector('input').value)
                    };
                }
            });

            if (program.length === 0) {
                showStatus('请先添加程序步骤', true);
                return;
            }

            fetch(`http://${getServerIP()}/program`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(program)
            })
                .then(response => {
                    if (!response.ok) throw new Error('网络请求失败');
                    return response.text();
                })
                .then(data => {
                    showStatus('程序开始执行');
                })
                .catch(error => {
                    showStatus('程序执行失败: ' + error.message, true);
                });
        }

        function clearProgram() {
            const programArea = document.getElementById('program-area');
            programArea.innerHTML = '<div class="placeholder">拖动左侧积木块到这里开始编程</div>';
        }

        // 页面加载时设置 IP
        document.addEventListener('DOMContentLoaded', () => {
            document.getElementById('ipHost').value = getServerIP();
            initDragAndDrop();
        });


        // 初始化拖放功能
        document.addEventListener('DOMContentLoaded', initDragAndDrop);
    </script>
</body>
</html>
)rawliteral";