var canvas = document.getElementById('canvas');
var ctx = canvas.getContext('2d');
ctx.lineWidth = 10;

let x0 = 500;
let y0 = 500;

let l1 = 100;
let l2 = 100;

let N = 0;
let PHI, THETA;

control = () => {
    draw(PHI[N], THETA[N]);
    N++;
};

prepareData = (text) => {
    let phiValues = [];
    let thetaValues = [];
    let tmp = text.split(/\r?\n/);
    
    for (let i = 0; i < tmp.length; i++){
        let pair = tmp[i].split(";");
        phiValues.push(parseFloat(pair[0]));
        thetaValues.push(parseFloat(pair[1]));
    }
    return [phiValues, thetaValues];
};

readFile = (input) => {
    let file = input.files[0];
    let reader = new FileReader();
    reader.readAsText(file);

    reader.onload = function() {
        let data = prepareData(reader.result);
        let phi = data[0];
        let theta = data[1];
        PHI = phi;
        THETA = theta;
        setInterval(control, 100);
    };
};

draw = (phi, theta) => {
    console.log(phi, theta)
    ctx.clearRect(0, 0, 1000, 1000);

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

