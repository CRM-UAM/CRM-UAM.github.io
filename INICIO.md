---
layout: default
permalink: /
redirect_from:
  - /web/
  - /web/index.php/
AVISO: Éste es el repositorio GitHub, la web está en http://crm.ii.uam.es/
---


Bienvenid@ a la web oficial del Club de Robótica y Mecatrónica (CRM) de la [**Escuela Politécnica Superior**](http://www.eps.uam.es/) de la [**Universidad Autónoma de Madrid**](http://www.uam.es/).  

{% for post in site.posts limit:10 %}
{% if post.mostrarEnPortada %}
<div style="{{ post.estiloEnPortada }}">
    <h2>{{ post.title }}</h2>
    {{ post.content }}
</div><br/>
{% endif %}
{% endfor %}


Nuestro objetivo es apoyar a cualquier miembro de la comunidad universitaria que quiera llevar a cabo proyectos relacionados con la robótica.
Es decir, **tanto estudiantes como profesores pueden inscribirse y así disponer de un espacio de trabajo agradable con herramientas de uso común** (impresoras 3D, soldadores, multímetros, sierras, etc) **así como los materiales necesarios** (componentes y cables, motores, baterías, etc).

Además **disponemos de un [foro (lista de correo)](/contacto)** donde ayudarnos unos a otros, y periódicamente organizamos **diversas [actividades](/actividades)** para fomentar la robótica entre los estudiantes.  


* [**Blog de noticias**](/blog)  
* [**Historia del CRM-UAM**](/historia)  
* [**Actividades organizadas por el club**](/actividades)  
* [**Logotipo y marketing**](/logotipo)  
* [**Pantallas informativas**](/pantallas)  
* [**Temas administrativos**](/administrativo)  

Si te gusta la robótica, no dudes en [**ponerte en contacto**](/contacto) con nosotros, o directamente rellena el  

&gt;&gt; [Formulario de **inscripción** de nuevos miembros](/registro) &lt;&lt;
--

