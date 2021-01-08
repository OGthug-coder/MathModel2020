var canvas = document.getElementById('canvas');
var ctx = canvas.getContext('2d');
ctx.lineWidth = 10;

let x0 = 700 / 2;
let y0 = 700 / 2;

let l1 = 100;
let l2 = 100;

let N = 0;
let PHI, THETA;

let timer;

prepareData = (text) => {
    let phiValues = [];
    let thetaValues = [];
    let tmp = text.split(/\r?\n/);

    for (let i = 0; i < tmp.length; i++) {
        let pair = tmp[i].split(";");
        phiValues.push(parseFloat(pair[0]));
        thetaValues.push(parseFloat(pair[1]));
    }
    return [phiValues, thetaValues];
};

stopModel = () => {
    clearInterval(timer);
    N = 0;
};

startModel = () => {
    if (N !== 0) stopModel()
    fetchData();
};

fetchData = () => {
    let body = {
        steps: document.getElementById("steps").value,
        l_1: document.getElementById("l_1").value,
        l_2: document.getElementById("l_2").value,
        m_1: document.getElementById("m_1").value,
        m_2: document.getElementById("m_2").value,
        angle_1: document.getElementById("angle_1").value,
        angle_2: document.getElementById("angle_2").value,
        speed_1: document.getElementById("speed_1").value,
        speed_2: document.getElementById("speed_2").value
    };

    for (let [key, value] of Object.entries(body)) {
        // convert deg to rad
        if (key.includes("angle")) {
            value = (parseInt(value) * Math.PI / 180).toFixed(2);
        }
        body[key] = parseFloat(value);
    }

    console.log(body);

    fetch("http://localhost:8085", {method: "POST", body: JSON.stringify(body)})
        .then(response => response.text())
        .then(text => {
            let data = prepareData(text);
            let phi = data[0];
            let theta = data[1];
            PHI = phi;
            THETA = theta;
            timer = setInterval(() => {
                draw(PHI[N], THETA[N]);
                N++;
                if (PHI[N] === undefined || THETA[N] === undefined) {
                    clearInterval(timer);
                }
            }, 100);
        });
};

// readFile = (input) => {
//     let file = input.files[0];
//     let reader = new FileReader();
//     reader.readAsText(file);
//
//     reader.onload = function () {
//         let data = prepareData(reader.result);
//     };
// };

draw = (phi, theta) => {
    ctx.clearRect(0, 0, 700, 700);

    ctx.beginPath();
    ctx.arc(x0, y0, 10, 0, 2 * Math.PI);
    ctx.fill();

    ctx.strokeStyle = "red";
    ctx.beginPath();
    ctx.moveTo(x0, y0);
    ctx.lineTo(x0 + l1 * Math.sin(phi), y0 + l1 * Math.cos(phi));
    ctx.stroke();

    ctx.strokeStyle = "blue";
    ctx.beginPath();
    ctx.moveTo(x0 + l1 * Math.sin(phi), y0 + l1 * Math.cos(phi));
    ctx.lineTo(x0 + l1 * Math.sin(phi) + l2 * Math.sin(theta), y0 + l1 * Math.cos(phi) + l2 * Math.cos(theta));
    ctx.stroke();
};

