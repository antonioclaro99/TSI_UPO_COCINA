# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Aulas(models.Model):
     _name = 'cocina.aulas'
     _description = 'cocina aulas'
     _rec_name='nAula'

     nAula = fields.Integer(string="Numero aula", required=True, help="Numero de nuestro aula")
     capacidadMax = fields.Integer('Capacidad maxima', help="Capacidad maxima de nuestro aula")
     puestos_ids = fields.Many2many("cocina.puestos",string="Lista de puestos")

     _sql_constraints = [('aulas_nAula_unique','UNIQUE (nAula)','El nAula debe ser único')]


     @api.constrains('puestos_ids')
     def capacidad(self):
        for aula in self:
             if len(aula.puestos_ids) > aula.capacidadMax:
                  mensaje = "La capacidad maxima es de " + str(aula.capacidadMax) + " puestos"
                  raise models.ValidationError(mensaje)