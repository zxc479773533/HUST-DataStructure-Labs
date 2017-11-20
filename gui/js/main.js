// arrays to store the form htmls
var linearListForm = [];
var linkListForm = [];
var binaryTreeForm = [];
var graphForm = [];

// push forms in array
linearListForm.push({
    value: 'InitList',
    args: [
        'ID'
    ],
});

linearListForm.push({
    value: 'DistoryList',
    args: [
        'ID'
    ],
});

linearListForm.push({
    value: 'ClearList',
    args: [
        'ID'
    ],
});


linearListForm.push({
    value: 'IsEmpty',
    args: [
        'ID'
    ],
});


linearListForm.push({
    value: 'ListLength',
    args: [
        'ID'
    ],
});


linearListForm.push({
    value: 'GetItem',
    args: [
        'ID',
        'Index'
    ],
});


linearListForm.push({
    value: 'LocateItem',
    args: [
        'ID',
        'Elem'
    ],
});


linearListForm.push({
    value: 'GetPiror',
    args: [
        'ID',
        'Index'
    ],
});


linearListForm.push({
    value: 'GetNext',
    args: [
        'ID',
        'Index'
    ],
});


linearListForm.push({
    value: 'ListInsert',
    args: [
        'ID',
        'Index'
    ],
});


linearListForm.push({
    value: 'ListDelete',
    args: [
        'ID',
        'Index'
    ],
});


linearListForm.push({
    value: 'PrintList',
    args: [
        'ID'
    ],
});

linearListForm.push({
    value: 'LsList',
    args: [],
});

// create arguments
function createArguments(arg) {
    
    var li = new String('<li><label class="argName">');
    li += arg;
    li += '<span class="compusory">*</span>';
    li += '</label><br/>';
    li += '<input type="text" class="inputZone" id="' + arg;
    li += '"/></li>';
    return li;
}

// create button
function createButton(mode) {
    
    // build button
    var button = new String('<br/><li><input id="submit" type="submit" value="提交" onclick=\'');
    button += 'mainSend("' + document.getElementById('choose_structure').value + '", "' + mode.value + '"';

    // build compulsory arguments
    mode.args.forEach(function (arg) {
        button += ', document.getElementById("' + arg + '").value';
    });

    button += ')\'/></li>';
    return button;
}

// create a form
function createForm(mode) {

    var form = new String('<br/><br/><ul class="userForm">');

    // create arguments
    mode.args.forEach(function (arg) {
        form += createArguments(arg);
        form += '<br/>';    
    });

    // create button
    form += createButton(mode);

    // end
    form += '</ul>';

    return form;
}

// main function to make form's inner HTML
function makeFormHTML(structure, func) {

    var HTML = '';

    // find the func
    if (structure == 'Linearlist') {
        linearListForm.forEach(function (mode) {
            if (mode.value == func) {
                HTML = createForm(mode);
            }
        });
    }
    else if (structure == 'Linklist') {
        linkListForm.forEach(function (mode) {
            if (mode.value == func) {
                HTML = createForm(mode);
            }
        });
    }
    else if (structure == 'Binarytree') {
        binaryTreeForm.forEach(function (mode) {
            if (mode.value == func) {
                HTML = createForm(mode);
            }
        });
    }
    else if (structure == 'Graph') {
        graphForm.forEach(function (mode) {
            if (mode.value == func) {
                HTML = createForm(mode);
            }
        });
    }

    return HTML;
}

// create functionchoose
function makeFuncChoose(val) {
    var HTML = '';
    HTML += '<br/>'
    if (val == 'Linearlist') {
        HTML += '<select id="choose_function" onchange="makeForm(getElementById(\'choose_structure\').value, getElementById(\'choose_function\').value)">';
        HTML += '<option value="Main">请选择要演示的功能</option>';
        HTML += '<option value="InitList">创建链表</option>';
        HTML += '<option value="DistoryList">销毁链表</option>';
        HTML += '<option value="ClearList">清空链表</option>';
        HTML += '<option value="IsEmpty">判定空表</option>';
        HTML += '<option value="ListLength">求表长</option>';
        HTML += '<option value="GetItem">获得元素</option>';
        HTML += '<option value="LocateItem">查找元素</option>';
        HTML += '<option value="GetPiror">获得前驱</option>';
        HTML += '<option value="GetNext">获得后继</option>';
        HTML += '<option value="ListInsert">插入元素</option>';
        HTML += '<option value="ListDelete">删除元素</option>';
        HTML += '<option value="PrintList">遍历并打印表</option>';
        HTML += '<option value="LsList">列出所有的线性表</option>';
    }
    else if (val == 'Linklist') {
        pass;
    }
    else if (val == 'Binarytree') {
        pass;
    }
    else if (val == 'Graph') {
        pass;
    }

    HTML += '</select>';
    HTML += '<form id="funcForm" onsubmit="return false;">';

    return HTML;
}

// create main control button
function makeMainButton() {
    var HTML = '<br/><br/><br/>';
    HTML += '<ul><li><h3 style="color:aliceblue;">点击清空所有数据</h3></li>';
    HTML += '<li><input id="submit" type="submit" value="清空" onclick="ws.send(\'Clear\')"/>';
    HTML += '</li></ul>';
    return HTML;
}