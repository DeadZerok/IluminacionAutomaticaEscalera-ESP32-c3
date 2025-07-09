#ifndef PAGE_H
#define PAGE_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Control de Escalera</title>

  <!-- Bootstrap -->
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.5/dist/css/bootstrap.min.css" rel="stylesheet"
    integrity="sha384-SgOJa3DmI69IUzQ2PVdRZhwQ+dy64/BUtbMJw1MZ8t5HZApcHrRKUc4W0kG879m7" crossorigin="anonymous">

  <!-- CSS -->
  <link rel="stylesheet" type="text/css" href="/style.css">
</head>

<body>
  <div class="container-fluid p-0 m-0">
    <nav class="navbar navbar-custom">
      <div class="container-fluid">
        <a class="navbar-brand ms-4 p-2" href="#">Escalera Inteligente</a>
      </div>
    </nav>

    <section class="hero d-flex justify-content-start align-items-center">
      <div class="hero-principal">
        <!-- Botones de encendido -->
        <div class="d-flex flex-column flex-md-row justify-content-center py-5 gap-5">
          <div class="boxEncendido d-flex flex-column p-3 align-items-center">
            <h4 class="m-4">Encendido superior Escalera</h4>
            <p>Estado del bombillo superior: <span id="estadoArriba">OFF</span></p>
            <div class="estado" id="iconoEstadoArriba"></div>
            <button class="cta" onclick="toggleLED('arriba')"><span>Encender/Apagar</span></button>
          </div>

          <div class="boxEncendido d-flex flex-column p-3 align-items-center">
            <h4 class="m-4">Encendido inferior Escalera</h4>
            <p>Estado del bombillo inferior: <span id="estadoAbajo">OFF</span></p>
            <div class="estado" id="iconoEstadoAbajo"></div>
            <button class="cta" onclick="toggleLED('abajo')"><span>Encender/Apagar</span></button>
          </div>
        </div>

        <!-- Sensores -->
        <div class="d-flex flex-column flex-md-row justify-content-center py-5 gap-5">
          <div class="boxMedicion d-flex flex-column p-3 align-items-center">
            <h4>Medición de distancia superior</h4>
            <div class="range-box p-4 my-4">
              <p><strong>Distancia sensor arriba:</strong> <span id="distArriba">0</span> cm</p>
              <div class="range-group">
                <input type="range" id="rangeArriba" min="10" max="100" step="1" value="70"
                  oninput="updateOutput('rangeArriba', 'outputArriba', 'arriba')">
                <output id="outputArriba" class="side">70</output>
              </div>
              <p class="mt-2">Activar en esta distancia</p>
            </div>
          </div>

          <div class="boxMedicion d-flex flex-column p-3 align-items-center">
            <h4>Medición de distancia inferior</h4>
            <div class="range-box p-4 my-4">
              <p><strong>Distancia sensor abajo:</strong> <span id="distAbajo">0</span> cm</p>
              <div class="range-group">
                <input type="range" id="rangeAbajo" min="10" max="100" step="1" value="50"
                  oninput="updateOutput('rangeAbajo', 'outputAbajo', 'abajo')">
                <output id="outputAbajo" class="side">50</output>
              </div>
              <p class="mt-2">Activar en esta distancia</p>
            </div>
          </div>
        </div>
      </div>
    </section>
  </div>

  <!-- Bootstrap JS -->
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.5/dist/js/bootstrap.bundle.min.js"
    integrity="sha384-k6d4wzSIapyDyv1kpU366/PK5hCdSbCRGRCMv+eplOQJWyd1fbcAu9OCUj5zNLiq"
    crossorigin="anonymous"></script>

  <!-- JavaScript Externo -->
  <script src="/script.js"></script>

</body>
</html>
)rawliteral";

#endif // PAGE_H
