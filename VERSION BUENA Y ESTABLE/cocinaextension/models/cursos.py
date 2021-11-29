
from odoo import models, fields, api


class Cursos(models.Model):
    _inherit = 'cocina.cursos'


    chef_id = fields.Many2one("cocinaextension.chefs",string="Chef que imparte el curso")
    alumnos_id = fields.Many2many("cocinaextension.alumnos",string="Lista de alumnos")
    totalPersonas  = fields.Integer("Personas apuntadas", compute='_compute_totalPersonas',store=True)

    @api.depends('alumnos_id')
    def _compute_totalPersonas(self):
        for record in self:
            record.totalPersonas=len(record.alumnos_id)