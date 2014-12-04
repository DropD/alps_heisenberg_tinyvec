import markdown
from markdown.extensions.extra import ExtraExtension
from markdown.extensions.codehilite import CodeHiliteExtension
import jinja2

if __name__ == '__main__':
    env = jinja2.Environment(loader = jinja2.FileSystemLoader('.'))

    xts = [ExtraExtension(), CodeHiliteExtension()]

    with open('howto.md') as howto:
        content = markdown.markdown(howto.read(), extensions=xts)

    tmpl = env.get_template('template.html')

    with open('howto.html', 'w') as result:
        result.write(tmpl.render(content = content).encode('utf8'))
