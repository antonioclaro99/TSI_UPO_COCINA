
from odoo import models, fields, api


class Cursos(models.Model):
    _inherit = 'cocina.cursos'


    chef_id = fields.Many2one("cocinaextension.chefs",string="Chef que imparte el curso")
    alumnos_id = fields.Many2many("cocinaextension.alumnos",string="Lista de alumnos")