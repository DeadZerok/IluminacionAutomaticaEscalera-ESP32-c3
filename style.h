#ifndef STYLE_H
#define STYLE_H

// Almacena el CSS en PROGMEM para ahorrar RAM
const char style_css[] PROGMEM = R"rawliteral(
/* Estilos generales */

section {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
}

.navbar {
  background-color: #BDE3E4;
  padding: 10px;
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
}

.navbar-custom .navbar-brand {
  color: #234567;
  font-size: 1.3rem;
  font-weight: bold;
}

.navbar-custom .navbar-brand:hover {
  color: #9EBABD;
}

.hero {
  background-color: #fdfaf6cb;
  min-height: 100vh;
}

.hero-principal {
  display: flex;
  flex-direction: column; 
  padding-top: 5rem;
}

.hero-principal .boxEncendido {
  
  display: flex;
  flex-direction: column;
  
  backdrop-filter: blur(5px); background-color: #ffff; border-radius: 26px; box-shadow: 35px 35px 68px 0px rgba(93, 162, 156, 0.5), inset -8px -8px 16px 0px rgba(157, 205, 204, 0.6), inset 0px 11px 28px 0px rgb(255, 255, 255);
  
}

.hero-principal button {
 
  margin-top: 1rem;
  margin-bottom:1rem;
}

.hero-principal .parrafo {
 
  margin-top: 1rem;
  
}
.hero-principal .boxMedicion {
  
  display: flex;
  margin-bottom: 3rem;
  
  flex-direction: column;
  backdrop-filter: blur(5px); background-color: #ffff; border-radius: 26px; box-shadow: 35px 35px 68px 0px rgba(93, 162, 156, 0.5), inset -8px -8px 16px 0px rgba(157, 205, 204, 0.6), inset 0px 11px 28px 0px rgb(255, 255, 255);
  
}

.cta {
  position: relative;
  margin: auto;
  padding: 12px 18px;
  transition: all 0.2s ease;
  border: none;
  background: none;
  cursor: pointer;
}

.cta:before {
  content: "";
  position: absolute;
  top: 0;
  left: 0;
  display: block;
  border-radius: 50px;
  background: #5DA29C;
  width: 45px;
  height: 45px;
  transition: all 0.3s ease;
}

.cta span {
  position: relative;
  font-family: "Ubuntu", sans-serif;
  font-size: 18px;
  font-weight: 700;
  letter-spacing: 0.05em;
  color: #234567;
}

.cta:hover:before {
width: 100%;
background: #BDE3E4;
}

.estado {
  display: flex;
  justify-content: center;
  align-items: center;
  margin-top: 1px;
  height: 40px;
}

/* Sol */
.sun {
  position: relative;
  width: 14px;
  height: 14px;
  margin-top: 5px;
  animation: spin 20s linear infinite;
}

.sun-core {
  width: 100%;
  height: 100%;
  background: #FFD93D;
  border-radius: 50%;
  box-shadow: 0 0 10px #FFD93D;
}

.sun-ray {
  position: absolute;
  background: #FFD93D;
  width: 4px;
  height: 12px;
  top: 0%;
  left: 30%;
  transform-origin: center;
}

.ray1 { transform: translate(-50%, -20px); }
.ray2 { transform: rotate(45deg) translate(-50%, -20px); }
.ray3 { transform: rotate(90deg) translate(-50%, -20px); }
.ray4 { transform: rotate(135deg) translate(-50%, -20px); }
.ray5 { transform: rotate(180deg) translate(-50%, -20px); }
.ray6 { transform: rotate(225deg) translate(-50%, -20px); }
.ray7 { transform: rotate(270deg) translate(-50%, -20px); }
.ray8 { transform: rotate(315deg) translate(-50%, -20px); }

@keyframes spin {
  from { transform: rotate(0deg); }
  to { transform: rotate(360deg); }
}

/* Luna y sus fases */
/* Luna y sus fases */
.moon {
  position: relative;
  width: 30px;
  height: 30px;
  margin-top: 5px;
  background: #f7eeba;
  border-radius: 50%;
  box-shadow: 0 0 10px rgba(255, 255, 255, 0.5);
  overflow: hidden;
  /* Aumentamos la duración de 12s a 24s para una animación más lenta */
  animation: moonPhases 32s ease-in-out infinite;
}

/* Sombra que se mueve para simular las fases */
.moon::before {
  content: '';
  position: absolute;
  width: 30px;
  height: 30px;
  border-radius: 50%;
  background: rgba(49, 65, 99, 0.9);
  top: 0;
  left: -30px;
  /* Aumentamos la duración de 12s a 24s para una animación más lenta */
  animation: moonShadow 32s ease-in-out infinite;
}

/* Animación de las fases de la luna con transiciones más suaves */
@keyframes moonShadow {
  /* Luna nueva (sombra cubre toda la luna) */
  0%, 100% {
    left: 0px;
    background: rgba(49, 65, 99, 0.95);
  }
  
  /* Cuarto creciente (sombra cubriendo la izquierda) */
  25% {
    left: -15px;
    background: rgba(49, 65, 99, 0.9);
  }
  
  /* Luna llena (sombra fuera de vista) */
  50% {
    left: -30px;
    background: rgba(49, 65, 99, 0.9);
  }
  
  /* Cuarto menguante (sombra cubriendo la derecha) */
  75% {
    left: 15px;
    background: rgba(49, 65, 99, 0.9);
  }
}

/* Ligero brillo de la luna */
@keyframes moonPhases {
  0%, 100% {
    box-shadow: 0 0 5px rgba(255, 255, 255, 0.3);
  }
  
  50% {
    box-shadow: 0 0 15px rgba(255, 255, 255, 0.7);
  }
}

/* Cráteres lunares para mayor detalle */
.moon::after {
  content: '';
  position: absolute;
  width: 5px;
  height: 5px;
  border-radius: 50%;
  background: rgba(220, 220, 220, 0.6);
  top: 8px;
  left: 10px;
  box-shadow: 
    8px 4px 0 -1px rgba(220, 220, 220, 0.6),
    -5px 10px 0 -1px rgba(220, 220, 220, 0.5),
    3px -3px 0 -1px rgba(220, 220, 220, 0.4);
}

/* ------------------barra de rango --------------------------- */


/* Cajita general */
.range-box {
background-color: #e0f7fa; /* Azul cielo */
border-radius: 20px;
box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1);
width: 90%;
max-width: 500px;
margin: auto;
}

/* Cada sección de sensor */
.sensor-section {
margin-bottom: 30px;
}

/* Grupo del input y output */
.range-group {
display: flex;
align-items: center;
gap: 15px;
}

input[type="range"] {
  -webkit-appearance: none;
  width: 100%;
  height: 8px;
  border-radius: 5px;
  background-color: #e9e4e4;      /* color de fondo “vació” */
  background-image: linear-gradient(
    90deg,
    #1e5757,                       /* color de “relleno” */
    #1e5757
  );
  background-repeat: no-repeat;
  background-size: 0% 100%;       /* inicialmente 0% de relleno */
  outline: none;
  transition: background-size 0.4s;
}


/* Thumb del range */
input[type="range"]::-webkit-slider-thumb {
-webkit-appearance: none;
appearance: none;
width: 22px;
height: 22px;
background: #607B7D;
border-radius: 50%;
cursor: pointer;
border: none;
}

input[type="range"]::-moz-range-thumb {
width: 22px;
height: 22px;
background: #37474F;
border-radius: 50%;
cursor: pointer;
border: none;
}

/* El valor (output) al lado */
output.side {
min-width: 40px;
text-align: center;
font-size: 1rem;
font-weight: bold;
color: #37474F;
}
)rawliteral";

#endif  // STYLE_H
