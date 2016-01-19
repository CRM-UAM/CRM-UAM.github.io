---
layout: default
permalink: /
redirect_from:
  - /web/
  - /web/index.php/
AVISO: Éste es el repositorio GitHub, la web está en http://crm.ii.uam.es/
---


Bienvenid@ a la web oficial del Club de Robótica y Mecatrónica (CRM) de la [**Escuela Politécnica Superior**](http://www.eps.uam.es/) de la [**Universidad Autónoma de Madrid**](http://www.uam.es/).  

<div style="border-radius: 25px; background: #fcf8dd; border: 3px solid #fcdb05; padding: 20px; width: 100%;">
{% for post in site.posts limit:1 %}
  <h2>
    <a class="post-link" href="{{ post.url | prepend: site.baseurl }}">{{ post.title }}</a>
  </h2>
  {{ post.content }}
{% endfor %}
</div><br/>

Nuestro objetivo es apoyar a cualquier miembro de la comunidad universitaria que quiera llevar a cabo proyectos relacionados con la robótica.
Es decir, **tanto estudiantes como profesores pueden inscribirse y así disponer de un espacio de trabajo agradable con herramientas de uso común** (impresoras 3D, soldadores, multímetros, sierras, etc) **así como los materiales necesarios** (componentes y cables, motores, baterías, etc).

Además **disponemos de un [foro](/contacto)** donde ayudarnos unos a otros, y periódicamente organizamos **diversas [actividades](/actividades)** para fomentar la robótica entre los estudiantes.  


* [**Blog de noticias**](/blog)  
* [**Historia del CRM-UAM**](/historia)  
* [**Actividades organizadas por el club**](/actividades)  
* [**Logotipo**](/logotipo)  
* [**Pantallas informativas**](/pantallas)  
* [**Temas administrativos**](/administrativo)  

Si te gusta la robótica, no dudes en [**ponerte en contacto**](/contacto) con nosotros.  

