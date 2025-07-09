#ifndef SCRIPT_H
#define SCRIPT_H

const char script_js[] PROGMEM = R"rawliteral(
  
function actualizarIconoEstado(idEstado, idIcono) {
  const estado = document.getElementById(idEstado).textContent.trim();
  const icono = document.getElementById(idIcono);

  if (estado === "ON") {
    icono.innerHTML = `
      <div class="sun">
        <div class="sun-core"></div>
        <div class="sun-ray ray1"></div>
        <div class="sun-ray ray2"></div>
        <div class="sun-ray ray3"></div>
        <div class="sun-ray ray4"></div>
        <div class="sun-ray ray5"></div>
        <div class="sun-ray ray6"></div>
        <div class="sun-ray ray7"></div>
        <div class="sun-ray ray8"></div>
      </div>`;
  } else {
    icono.innerHTML = `<div class="moon"></div>`;
  }
}

function toggleLED(zona) {
  fetch(`/toggle?led=${zona}`)
    .then(response => response.text())
    .then(text => {
      console.log(text);
      getStatus();
    })
    .catch(error => console.error('Error:', error));

  if (zona === 'arriba') {
    const estadoSpan = document.getElementById('estadoArriba');
    estadoSpan.textContent = estadoSpan.textContent.trim() === 'OFF' ? 'ON' : 'OFF';
    actualizarIconoEstado('estadoArriba', 'iconoEstadoArriba');
  } else if (zona === 'abajo') {
    const estadoSpan = document.getElementById('estadoAbajo');
    estadoSpan.textContent = estadoSpan.textContent.trim() === 'OFF' ? 'ON' : 'OFF';
    actualizarIconoEstado('estadoAbajo', 'iconoEstadoAbajo');
  }
}

  function updateSliderFill(idRange) {
  const range = document.getElementById(idRange);
  // calcula el % de relleno
  const percent = (range.value - range.min) / (range.max - range.min) * 100;
  // aplica al background-size del propio input
  range.style.backgroundSize = `${percent}% 100%`;
}

// Al mover arriba
document.getElementById('rangeArriba')
  .addEventListener('input', () => {
    updateSliderFill('rangeArriba');
    updateOutput('rangeArriba','outputArriba','arriba');
});

// Al mover abajo
document.getElementById('rangeAbajo')
  .addEventListener('input', () => {
    updateSliderFill('rangeAbajo');
    updateOutput('rangeAbajo','outputAbajo','abajo');
});

// Inicializa al cargar la página
window.addEventListener('DOMContentLoaded', () => {
  updateSliderFill('rangeArriba');
  updateSliderFill('rangeAbajo');
});


    function updateOutput(rangeId, outputId, sensor) {
      const range = document.getElementById(rangeId);
      const output = document.getElementById(outputId);

      output.value = range.value;

      // Cambiar fondo dinámico
      const percent = (range.value - range.min) / (range.max - range.min) * 100;
      range.style.background = `linear-gradient(90deg, #607B7D ${percent}%, #ddd ${percent}%)`;

      // Enviar valor al ESP32
      fetch(`/setThreshold?sensor=${sensor}&value=${range.value}`)
        .then(response => response.text())
        .then(data => console.log(data))
        .catch(error => console.error('Error enviando umbral:', error));
    }


function getStatus() {
  fetch('/status')
    .then(response => response.json())
    .then(data => {
      document.getElementById('distAbajo').innerText = data.distAbajo;
      document.getElementById('distArriba').innerText = data.distArriba;
      document.getElementById('estadoAbajo').innerText = data.ledAbajo ? 'ON' : 'OFF';
      document.getElementById('estadoArriba').innerText = data.ledArriba ? 'ON' : 'OFF';
      actualizarIconoEstado('estadoArriba', 'iconoEstadoArriba');
      actualizarIconoEstado('estadoAbajo', 'iconoEstadoAbajo');
    });
}

document.addEventListener('DOMContentLoaded', function () {
  getStatus();
  setInterval(getStatus, 1000);
  actualizarIconoEstado('estadoArriba', 'iconoEstadoArriba');
  actualizarIconoEstado('estadoAbajo', 'iconoEstadoAbajo');
});
)rawliteral";

#endif  // SCRIPT_H
