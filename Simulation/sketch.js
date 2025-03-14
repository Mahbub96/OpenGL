let simulation;

function setup() {
  simulation = new Simulation();
  simulation.setup();
}

function draw() {
  simulation.draw();
}

function keyPressed() {
  simulation.keyPressed();
}

class CelestialBody {
  constructor(position, mass, radius, velocity, color, curvatureMultiplier = 0, curvatureOffset = 0, isLightSource = false) {
    this.position = position.copy();
    this.mass = mass;
    this.radius = radius;
    this.velocity = velocity.copy();
    this.color = color;
    this.curvatureMultiplier = curvatureMultiplier;
    this.curvatureOffset = curvatureOffset;
    this.isLightSource = isLightSource;
  }

  applyForce(force, deltaTime) {
    let acceleration = p5.Vector.div(force, this.mass);
    acceleration.mult(deltaTime);
    this.velocity.add(acceleration);
  }

  update(deltaTime) {
    this.position.add(p5.Vector.mult(this.velocity, deltaTime));
  }

  draw() {
    push();
    translate(this.position.x, this.position.y);
    if (this.isLightSource) {
      pointLight(255, 255, 220, 0, 0, 0);
    }
    emissiveMaterial(...this.color);
    sphere(this.radius);
    pop();
  }

  static calculateGravity(body1, body2, G) {
    const direction = p5.Vector.sub(body2.position, body1.position);
    const distance = direction.mag();
    if (distance === 0) return createVector(0, 0);
    direction.normalize();
    const strength = (G * body1.mass * body2.mass) / (distance * distance);
    return direction.mult(strength);
  }
}

class OrbitPath {
  constructor(maxLength) {
    this.points = [];
    this.maxLength = maxLength;
  }

  addPosition(position) {
    this.points.push(position.copy());
    if (this.points.length > this.maxLength) this.points.shift();
  }

  draw(col) {
    noFill();
    stroke(col);
    beginShape();
    this.points.forEach(pos => vertex(pos.x, pos.y));
    endShape();
  }
}

class SpacetimeGrid {
  constructor(gridSpacing, range, curvatureScale) {
    this.gridSpacing = gridSpacing;
    this.range = range;
    this.curvatureScale = curvatureScale;
    this.grid = [];
    this.createGrid();
  }

  createGrid() {
    for (let x = -this.range; x <= this.range; x += this.gridSpacing) {
      let col = [];
      for (let y = -this.range; y <= this.range; y += this.gridSpacing) {
        col.push(createVector(x, y, 0));
      }
      this.grid.push(col);
    }
  }

  updateCurvature(bodies) {
    for (let x = 0; x < this.grid.length; x++) {
      for (let y = 0; y < this.grid[x].length; y++) {
        const point = this.grid[x][y];
        let z = 0;
        bodies.forEach(body => {
          const d = dist(point.x, point.y, body.position.x, body.position.y);
          z -= (body.mass * body.curvatureMultiplier) / (d + body.curvatureOffset);
        });
        point.z = z * this.curvatureScale;
      }
    }
  }

  draw() {
    stroke(120, 180, 255, 120);
    strokeWeight(1.2);
    noFill();
    for (let x = 0; x < this.grid.length - 1; x++) {
      for (let y = 0; y < this.grid[x].length - 1; y++) {
        beginShape();
        vertex(this.grid[x][y].x, this.grid[x][y].y, this.grid[x][y].z);
        vertex(this.grid[x+1][y].x, this.grid[x+1][y].y, this.grid[x+1][y].z);
        vertex(this.grid[x+1][y+1].x, this.grid[x+1][y+1].y, this.grid[x+1][y+1].z);
        vertex(this.grid[x][y+1].x, this.grid[x][y+1].y, this.grid[x][y+1].z);
        endShape(CLOSE);
      }
    }
  }
}

class Simulation {
  constructor() {
    this.G = 0.2;
    this.deltaTime = 0.8;
    this.celestialBodies = [];
    this.earthOrbit = new OrbitPath(400);
    this.moonOrbit = new OrbitPath(100);
    this.spacetimeGrid = null;
  }

  setup() {
    createCanvas(1200, 800, WEBGL);
    angleMode(DEGREES);

    const sun = new CelestialBody(
      createVector(0, 0),
      100500,
      50,
      createVector(0, 0),
      [255, 225, 50],
      0.8,
      10,
      true
    );

    const earth = new CelestialBody(
      createVector(300, 0),
      3600,
      10,
      createVector(0, 8.5),
      [70, 130, 200],
      0.15,
      20
    );

    const moon = new CelestialBody(
      createVector(earth.position.x + 35, earth.position.y),
      100,
      3,
      createVector(0, 4.2).add(earth.velocity),
      [200, 200, 200],
      0.05,
      30
    );

    this.celestialBodies = [sun, earth, moon];
    this.spacetimeGrid = new SpacetimeGrid(30, 1, 1000);
    noStroke();
  }

  draw() {
    background(0);
    lights();
    orbitControl(1, 1, 0.1);
    translate(-width/4.5, -height/4.5);
    scale(0.75);

    this.updatePhysics();
    this.spacetimeGrid.updateCurvature(this.celestialBodies);
    this.spacetimeGrid.draw();
    this.drawCelestialBodies();
    this.drawOrbitPaths();
  }

  updatePhysics() {
    const [sun, earth, moon] = this.celestialBodies;

    const earthSunForce = CelestialBody.calculateGravity(earth, sun, this.G);
    const moonSunForce = CelestialBody.calculateGravity(moon, sun, this.G);
    const moonEarthForce = CelestialBody.calculateGravity(moon, earth, this.G);

    earth.applyForce(earthSunForce, this.deltaTime);
    moon.applyForce(p5.Vector.add(moonSunForce, moonEarthForce), this.deltaTime);

    earth.update(this.deltaTime);
    moon.update(this.deltaTime);

    this.earthOrbit.addPosition(earth.position);
    this.moonOrbit.addPosition(moon.position);
  }

  drawCelestialBodies() {
    this.celestialBodies.forEach(body => body.draw());
  }

  drawOrbitPaths() {
    this.earthOrbit.draw(color(50, 200, 100, 150));
    this.moonOrbit.draw(color(180, 180, 180, 120));
  }

  keyPressed() {
    if (key === 'p' || key === 'P') this.togglePause();
  }

  togglePause() {
    isLooping() ? noLoop() : loop();
  }
}