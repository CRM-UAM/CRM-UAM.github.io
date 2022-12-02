---
layout: default
permalink: /
redirect_from:
  - /web/
  - /web/index.php/
AVISO: Éste es el repositorio GitHub, la web está en http://crm.ii.uam.es/
---


¡Bienvenid@! Esta es la web oficial del Club de Robótica y Mecatrónica (CRM) de la [**Escuela Politécnica Superior**](http://www.eps.uam.es/) de la [**Universidad Autónoma de Madrid**](http://www.uam.es/). **¡Únete a [nuestro grupo de Telegram!](/registro)**




<table border="0" width="100%">
  <tr>
    <td>
      <a href="/calendario">
      <center><img src="/imagenes_web/iconos/calendario.png"/><br/><b>Calendario</b></center>
      </a>
    </td>
    <td>
      <a href="https://github.com/CRM-UAM/" target="_blank">
      <center><img src="/imagenes_web/iconos/cohete.png"/><br/><b>Proyectos</b></center>
      </a>
    </td>
    <td>
      <a href="/contacto">
      <center><img src="/imagenes_web/iconos/email.png"/><br/><b>Contacto</b></center>
      </a>
    </td>
    <td>
      <a href="/administrativo">
      <center><img src="/imagenes_web/iconos/administrativo.png"/><br/><b>Temas administrativos<br/>y transparencia</b></center>
      </a>
    </td>
  </tr>
  <tr>
    <td>
      <a href="/blog">
      <center><img src="/imagenes_web/iconos/difusion.png"/><br/><b>Blog de noticias</b></center>
      </a>
    </td>
    <td>
      <a href="/registro">
      <center><img src="/imagenes_web/iconos/nuevoCRMiembro.png"/><br/><b>¿Nuevo miembr@?</b></center>
      </a>
    </td>
    <td>
      <a href="/junta">
      <center><img src="/imagenes_web/iconos/cpu.png"/><br/><b>Junta directiva</b></center>
      </a>
    </td>
    <td>
      <a href="/historia">
      <center><img src="/imagenes_web/iconos/monitor.png"/><br/><b>Historia del club</b></center>
      </a>
    </td>
  </tr>
</table>


{% for post in site.posts limit:10 %}
{% if post.mostrarEnPortada %}
<div style="{{ post.estiloEnPortada }}">
    <h2>{{ post.title }}</h2>
    {{ post.content }}
</div><br/>
{% endif %}
{% endfor %}



Somos una asociación de estudiantes dedicados a fomentar el interés por la robótica en la [Universidad Autónoma de Madrid](http://www.uam.es/) y España en general.
Periódicamente organizamos talleres, competiciones y seminarios orientados a la difusión de la electrónica, la mecánica y el software.
También proporcionamos ayuda (técnica y económica) a los estudiantes que buscan realizar proyectos relacionados con la robótica.


Si te interesa no dudes en visitarnos, [**ponerte en contacto**](/contacto) con nosotros, o directamente rellenar el [formulario de **inscripción** de nuevos miembros](/registro)

