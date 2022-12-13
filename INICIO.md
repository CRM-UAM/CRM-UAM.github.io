---
layout: default
permalink: /
redirect_from:
  - /web/
  - /web/index.php/
AVISO: Éste es el repositorio GitHub, la web está en http://crm.ii.uam.es/
---


¡Bienvenid@! Esta es la web oficial del Club de Robótica y Mecatrónica (CRM) de la [**Escuela Politécnica Superior**](http://www.eps.uam.es/) de la [**Universidad Autónoma de Madrid**](http://www.uam.es/). **¡Únete a [nuestro grupo de Telegram!](/registro)**



{% for post in site.posts limit:10 %}
{% if post.mostrarEnPortada %}
<div style="{{ post.estiloEnPortada }}">
    <h2>{{ post.title }}</h2>
    {{ post.content }}
</div><br/>
{% endif %}
{% endfor %}



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
      <center><img src="/imagenes_web/iconos/nuevoCRMiembro.png"/><br/><b>¡Apúntate!</b></center>
      </a>
    </td>
    <td>
      <a href="/logotipo">
      <center><img src="/imagenes_web/iconos/monitor.png"/><br/><b>Logos y carteles</b></center>
      </a>
    </td>
    <td>
      <a href="/historia">
      <center><img src="/imagenes_web/iconos/cpu.png"/><br/><b>Historia del club</b></center>
      </a>
    </td>
  </tr>
</table>


El Club de Robótica-Mecatrónica está gestionado por estudiantes y apoya a cualquier miembro de la comunidad universitaria que quiera llevar a cabo proyectos relacionados con la robótica.

Es decir, tanto estudiantes como profesores pueden inscribirse y así **disponer de un espacio de trabajo agradable con herramientas de uso común (impresoras 3D, soldadores, sierras, alicates, destornilladores, etc) así como los materiales necesarios (cables, componentes, motores, baterías, etc)**.
Además tenemos un [grupo de Telegram](../registro) donde ayudarnos unos a otros ¡Únete!

Si te interesa no dudes en visitarnos, [ponerte en contacto](/contacto) con nosotros, o directamente rellenar el [**formulario de inscripción de nuevos miembros**](/registro) 👈

