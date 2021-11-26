
from odoo import models, fields, api


class Cursos(models.Model):
    _inherit = 'cocina.cursos'


    atributoNuevo = fields.Char("HOLA MATAME")
    chef_id = fields.Many2one("cocina.chefs",string="Chef que imparte el curso")
    alumnos_id = fields.Many2many("cocina.alumnos",string="Lista de alumnos")