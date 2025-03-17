let simulation;
let earthTexture;
let sunTexture;
let moonTexture;
let speedSlider;
let yearDuration = 300;
let speedFactor;

function preload() {
  earthTexture = loadImage("./earth.png");
  sunTexture = loadImage("./sun.png");
  moonTexture = loadImage(
    "https://upload.wikimedia.org/wikipedia/commons/thumb/e/e2/Full_moon.png/1024px-Full_moon.png"
  );
}

function setup() {
  createCanvas(800, 800, WEBGL);
  simulation = new Simulation();

  speedSlider = createSlider(1000, 4000, 3000, 1);
  speedSlider.position(10, height - 40);
  speedSlider.input(updateSpeed);

  updateSpeed();
}

function draw() {
  background(10, 10, 30);
  simulation.run();
}

function updateSpeed() {
  yearDuration = speedSlider.value();
  document.getElementById("speedValue").innerText = yearDuration / 10 + " sec";
  speedFactor = 600 / yearDuration;
  simulation.setSpeedFactor(speedFactor);
}

class CelestialBody {
  constructor(radius, textureImg = null, isSun = false, detail = 24) {
    this.radius = radius;
    this.textureImg = textureImg;
    this.isSun = isSun;
    this.position = createVector(0, 0, 0);
    this.detail = detail;
    this.rotationAngle = 0;
    this.rotationSpeed = 0.001;
  }

  updatePosition(x, y, z) {
    this.position.set(x, y, z);
  }

  updateRotation() {
    this.rotationAngle += this.rotationSpeed;
  }

  draw() {
    push();
    translate(this.position.x, this.position.y, this.position.z);

    if (!this.isSun) {
      rotateX(-3.5);
    }

    if (this.textureImg) {
      rotateY(this.rotationAngle);
      texture(this.textureImg);
    } else if (this.isSun) {
      rotateY(this.rotationAngle);
      texture(sunTexture);
    } else {
      ambientMaterial(255);
    }

    sphere(this.radius, this.detail, this.detail);
    pop();
  }
}

class Simulation {
  constructor() {
    this.earthOrbitRadius = 200;
    this.moonOrbitRadius = 50;
    this.angleEarth = 0;
    this.angleMoon = 0;
    this.speedFactor = 1;

    this.sun = new CelestialBody(50, sunTexture, true, 36);
    this.earth = new CelestialBody(20, earthTexture, false, 30);
    this.moon = new CelestialBody(10, moonTexture, false, 28);

    this.sun.rotationSpeed = 0.0009;
  }

  setSpeedFactor(factor) {
    this.speedFactor = factor;

    // Earth completes one orbit around the Sun in the given duration
    this.earthOrbitSpeed = ((2 * PI) / yearDuration) * this.speedFactor;

    // Moon orbits Earth 12 times per Earth orbit
    this.moonOrbitSpeed = this.earthOrbitSpeed * 12;

    // Earth rotates 30 times per Moon orbit
    this.earth.rotationSpeed = this.moonOrbitSpeed * 30;
  }

  run() {
    pointLight(255, 255, 255, -100, -100, 0);
    ambientLight(200, 200, 200);

    let lightDirection = createVector(0, 0, 0)
      .sub(this.sun.position)
      .normalize();
    directionalLight(
      255,
      255,
      255,
      lightDirection.x,
      lightDirection.y,
      lightDirection.z
    );

    orbitControl();

    let earthX = this.earthOrbitRadius * cos(this.angleEarth);
    let earthZ = this.earthOrbitRadius * 0.8 * sin(this.angleEarth);
    this.earth.updatePosition(earthX, 0, earthZ);
    this.earth.updateRotation();
    this.sun.updateRotation();

    let moonX = earthX + this.moonOrbitRadius * cos(this.angleMoon);
    let moonZ = earthZ + this.moonOrbitRadius * 0.9 * sin(this.angleMoon);
    this.moon.updatePosition(moonX, 0, moonZ);

    this.angleEarth += this.earthOrbitSpeed;
    this.angleMoon += this.moonOrbitSpeed;

    this.sun.draw();
    this.earth.draw();
    this.moon.draw();
  }
}
