/*!
 * /**
 * * @name JSON Editor
 * * @description JSON Schema Based Editor
 * * This library is the continuation of jdorn's great work (see also https://github.com/jdorn/json-editor/issues/800)
 * * @version "2.6.1"
 * * @author Jeremy Dorn
 * * @see https://github.com/jdorn/json-editor/
 * * @see https://github.com/json-editor/json-editor
 * * @license MIT
 * * @example see README.md and docs/ for requirements, examples and usage info
 * * /
 */
!(function(t, e) {
  if ('object' == typeof exports && 'object' == typeof module) module.exports = e();
  else if ('function' == typeof define && define.amd) define([], e);
  else {
    var r = e();
    for (var n in r) ('object' == typeof exports ? exports : t)[n] = r[n];
  }
})(window, function() {
  return (function(t) {
    var e = {};
    function r(n) {
      if (e[n]) return e[n].exports;
      var i = (e[n] = { i: n, l: !1, exports: {} });
      return t[n].call(i.exports, i, i.exports, r), (i.l = !0), i.exports;
    }
    return (
      (r.m = t),
      (r.c = e),
      (r.d = function(t, e, n) {
        r.o(t, e) || Object.defineProperty(t, e, { enumerable: !0, get: n });
      }),
      (r.r = function(t) {
        'undefined' != typeof Symbol && Symbol.toStringTag && Object.defineProperty(t, Symbol.toStringTag, { value: 'Module' }), Object.defineProperty(t, '__esModule', { value: !0 });
      }),
      (r.t = function(t, e) {
        if ((1 & e && (t = r(t)), 8 & e)) return t;
        if (4 & e && 'object' == typeof t && t && t.__esModule) return t;
        var n = Object.create(null);
        if ((r.r(n), Object.defineProperty(n, 'default', { enumerable: !0, value: t }), 2 & e && 'string' != typeof t))
          for (var i in t)
            r.d(
              n,
              i,
              function(e) {
                return t[e];
              }.bind(null, i)
            );
        return n;
      }),
      (r.n = function(t) {
        var e =
          t && t.__esModule
            ? function() {
                return t.default;
              }
            : function() {
                return t;
              };
        return r.d(e, 'a', e), e;
      }),
      (r.o = function(t, e) {
        return Object.prototype.hasOwnProperty.call(t, e);
      }),
      (r.p = '/dist/'),
      r((r.s = 160))
    );
  })([
    function(t, e, r) {
      var n = r(3),
        i = r(36).f,
        o = r(29),
        a = r(31),
        s = r(80),
        l = r(110),
        c = r(90);
      t.exports = function(t, e) {
        var r,
          u,
          h,
          d,
          p,
          f = t.target,
          y = t.global,
          m = t.stat;
        if ((r = y ? n : m ? n[f] || s(f, {}) : (n[f] || {}).prototype))
          for (u in e) {
            if (((d = e[u]), (h = t.noTargetGet ? (p = i(r, u)) && p.value : r[u]), !c(y ? u : f + (m ? '.' : '#') + u, t.forced) && void 0 !== h)) {
              if (typeof d == typeof h) continue;
              l(d, h);
            }
            (t.sham || (h && h.sham)) && o(d, 'sham', !0), a(r, u, d, t);
          }
      };
    },
    function(t, e) {
      t.exports = function(t) {
        try {
          return !!t();
        } catch (t) {
          return !0;
        }
      };
    },
    function(t, e, r) {
      var n = r(3),
        i = r(67),
        o = r(16),
        a = r(82),
        s = r(84),
        l = r(108),
        c = i('wks'),
        u = n.Symbol,
        h = l ? u : (u && u.withoutSetter) || a;
      t.exports = function(t) {
        return (o(c, t) && (s || 'string' == typeof c[t])) || (s && o(u, t) ? (c[t] = u[t]) : (c[t] = h('Symbol.' + t))), c[t];
      };
    },
    function(t, e, r) {
      (function(e) {
        var r = function(t) {
          return t && t.Math == Math && t;
        };
        t.exports =
          r('object' == typeof globalThis && globalThis) ||
          r('object' == typeof window && window) ||
          r('object' == typeof self && self) ||
          r('object' == typeof e && e) ||
          (function() {
            return this;
          })() ||
          Function('return this')();
      }.call(this, r(133)));
    },
    function(t, e, r) {
      var n = r(25),
        i = r(92),
        o = r(61),
        a = r(51),
        s = r(120),
        l = a.set,
        c = a.getterFor('Array Iterator');
      (t.exports = s(
        Array,
        'Array',
        function(t, e) {
          l(this, { type: 'Array Iterator', target: n(t), index: 0, kind: e });
        },
        function() {
          var t = c(this),
            e = t.target,
            r = t.kind,
            n = t.index++;
          return !e || n >= e.length
            ? ((t.target = void 0), { value: void 0, done: !0 })
            : 'keys' == r
            ? { value: n, done: !1 }
            : 'values' == r
            ? { value: e[n], done: !1 }
            : { value: [n, e[n]], done: !1 };
        },
        'values'
      )),
        (o.Arguments = o.Array),
        i('keys'),
        i('values'),
        i('entries');
    },
    function(t, e, r) {
      var n = r(83),
        i = r(31),
        o = r(136);
      n || i(Object.prototype, 'toString', o, { unsafe: !0 });
    },
    function(t, e, r) {
      var n = r(0),
        i = r(3),
        o = r(45),
        a = r(52),
        s = r(11),
        l = r(84),
        c = r(108),
        u = r(1),
        h = r(16),
        d = r(58),
        p = r(14),
        f = r(13),
        y = r(17),
        m = r(25),
        v = r(49),
        b = r(50),
        g = r(47),
        _ = r(57),
        w = r(54),
        k = r(142),
        x = r(89),
        j = r(36),
        O = r(15),
        E = r(70),
        C = r(29),
        S = r(31),
        A = r(67),
        P = r(66),
        T = r(68),
        R = r(82),
        I = r(2),
        L = r(118),
        N = r(119),
        B = r(93),
        V = r(51),
        D = r(44).forEach,
        F = P('hidden'),
        M = I('toPrimitive'),
        H = V.set,
        q = V.getterFor('Symbol'),
        U = Object.prototype,
        z = i.Symbol,
        $ = o('JSON', 'stringify'),
        J = j.f,
        G = O.f,
        W = k.f,
        Y = E.f,
        X = A('symbols'),
        K = A('op-symbols'),
        Z = A('string-to-symbol-registry'),
        Q = A('symbol-to-string-registry'),
        tt = A('wks'),
        et = i.QObject,
        rt = !et || !et.prototype || !et.prototype.findChild,
        nt =
          s &&
          u(function() {
            return (
              7 !=
              g(
                G({}, 'a', {
                  get: function() {
                    return G(this, 'a', { value: 7 }).a;
                  },
                })
              ).a
            );
          })
            ? function(t, e, r) {
                var n = J(U, e);
                n && delete U[e], G(t, e, r), n && t !== U && G(U, e, n);
              }
            : G,
        it = function(t, e) {
          var r = (X[t] = g(z.prototype));
          return H(r, { type: 'Symbol', tag: t, description: e }), s || (r.description = e), r;
        },
        ot = c
          ? function(t) {
              return 'symbol' == typeof t;
            }
          : function(t) {
              return Object(t) instanceof z;
            },
        at = function(t, e, r) {
          t === U && at(K, e, r), f(t);
          var n = v(e, !0);
          return (
            f(r), h(X, n) ? (r.enumerable ? (h(t, F) && t[F][n] && (t[F][n] = !1), (r = g(r, { enumerable: b(0, !1) }))) : (h(t, F) || G(t, F, b(1, {})), (t[F][n] = !0)), nt(t, n, r)) : G(t, n, r)
          );
        },
        st = function(t, e) {
          f(t);
          var r = m(e),
            n = _(r).concat(ht(r));
          return (
            D(n, function(e) {
              (s && !lt.call(r, e)) || at(t, e, r[e]);
            }),
            t
          );
        },
        lt = function(t) {
          var e = v(t, !0),
            r = Y.call(this, e);
          return !(this === U && h(X, e) && !h(K, e)) && (!(r || !h(this, e) || !h(X, e) || (h(this, F) && this[F][e])) || r);
        },
        ct = function(t, e) {
          var r = m(t),
            n = v(e, !0);
          if (r !== U || !h(X, n) || h(K, n)) {
            var i = J(r, n);
            return !i || !h(X, n) || (h(r, F) && r[F][n]) || (i.enumerable = !0), i;
          }
        },
        ut = function(t) {
          var e = W(m(t)),
            r = [];
          return (
            D(e, function(t) {
              h(X, t) || h(T, t) || r.push(t);
            }),
            r
          );
        },
        ht = function(t) {
          var e = t === U,
            r = W(e ? K : m(t)),
            n = [];
          return (
            D(r, function(t) {
              !h(X, t) || (e && !h(U, t)) || n.push(X[t]);
            }),
            n
          );
        };
      (l ||
        (S(
          (z = function() {
            if (this instanceof z) throw TypeError('Symbol is not a constructor');
            var t = arguments.length && void 0 !== arguments[0] ? String(arguments[0]) : void 0,
              e = R(t),
              r = function(t) {
                this === U && r.call(K, t), h(this, F) && h(this[F], e) && (this[F][e] = !1), nt(this, e, b(1, t));
              };
            return s && rt && nt(U, e, { configurable: !0, set: r }), it(e, t);
          }).prototype,
          'toString',
          function() {
            return q(this).tag;
          }
        ),
        S(z, 'withoutSetter', function(t) {
          return it(R(t), t);
        }),
        (E.f = lt),
        (O.f = at),
        (j.f = ct),
        (w.f = k.f = ut),
        (x.f = ht),
        (L.f = function(t) {
          return it(I(t), t);
        }),
        s &&
          (G(z.prototype, 'description', {
            configurable: !0,
            get: function() {
              return q(this).description;
            },
          }),
          a || S(U, 'propertyIsEnumerable', lt, { unsafe: !0 }))),
      n({ global: !0, wrap: !0, forced: !l, sham: !l }, { Symbol: z }),
      D(_(tt), function(t) {
        N(t);
      }),
      n(
        { target: 'Symbol', stat: !0, forced: !l },
        {
          for: function(t) {
            var e = String(t);
            if (h(Z, e)) return Z[e];
            var r = z(e);
            return (Z[e] = r), (Q[r] = e), r;
          },
          keyFor: function(t) {
            if (!ot(t)) throw TypeError(t + ' is not a symbol');
            if (h(Q, t)) return Q[t];
          },
          useSetter: function() {
            rt = !0;
          },
          useSimple: function() {
            rt = !1;
          },
        }
      ),
      n(
        { target: 'Object', stat: !0, forced: !l, sham: !s },
        {
          create: function(t, e) {
            return void 0 === e ? g(t) : st(g(t), e);
          },
          defineProperty: at,
          defineProperties: st,
          getOwnPropertyDescriptor: ct,
        }
      ),
      n({ target: 'Object', stat: !0, forced: !l }, { getOwnPropertyNames: ut, getOwnPropertySymbols: ht }),
      n(
        {
          target: 'Object',
          stat: !0,
          forced: u(function() {
            x.f(1);
          }),
        },
        {
          getOwnPropertySymbols: function(t) {
            return x.f(y(t));
          },
        }
      ),
      $) &&
        n(
          {
            target: 'JSON',
            stat: !0,
            forced:
              !l ||
              u(function() {
                var t = z();
                return '[null]' != $([t]) || '{}' != $({ a: t }) || '{}' != $(Object(t));
              }),
          },
          {
            stringify: function(t, e, r) {
              for (var n, i = [t], o = 1; arguments.length > o; ) i.push(arguments[o++]);
              if (((n = e), (p(e) || void 0 !== t) && !ot(t)))
                return (
                  d(e) ||
                    (e = function(t, e) {
                      if (('function' == typeof n && (e = n.call(this, t, e)), !ot(e))) return e;
                    }),
                  (i[1] = e),
                  $.apply(null, i)
                );
            },
          }
        );
      z.prototype[M] || C(z.prototype, M, z.prototype.valueOf), B(z, 'Symbol'), (T[F] = !0);
    },
    function(t, e, r) {
      var n = r(0),
        i = r(11),
        o = r(3),
        a = r(16),
        s = r(14),
        l = r(15).f,
        c = r(110),
        u = o.Symbol;
      if (i && 'function' == typeof u && (!('description' in u.prototype) || void 0 !== u().description)) {
        var h = {},
          d = function() {
            var t = arguments.length < 1 || void 0 === arguments[0] ? void 0 : String(arguments[0]),
              e = this instanceof d ? new u(t) : void 0 === t ? u() : u(t);
            return '' === t && (h[e] = !0), e;
          };
        c(d, u);
        var p = (d.prototype = u.prototype);
        p.constructor = d;
        var f = p.toString,
          y = 'Symbol(test)' == String(u('test')),
          m = /^Symbol\((.*)\)[^)]+$/;
        l(p, 'description', {
          configurable: !0,
          get: function() {
            var t = s(this) ? this.valueOf() : this,
              e = f.call(t);
            if (a(h, t)) return '';
            var r = y ? e.slice(7, -1) : e.replace(m, '$1');
            return '' === r ? void 0 : r;
          },
        }),
          n({ global: !0, forced: !0 }, { Symbol: d });
      }
    },
    function(t, e, r) {
      r(119)('iterator');
    },
    function(t, e, r) {
      var n = r(123).charAt,
        i = r(51),
        o = r(120),
        a = i.set,
        s = i.getterFor('String Iterator');
      o(
        String,
        'String',
        function(t) {
          a(this, { type: 'String Iterator', string: String(t), index: 0 });
        },
        function() {
          var t,
            e = s(this),
            r = e.string,
            i = e.index;
          return i >= r.length ? { value: void 0, done: !0 } : ((t = n(r, i)), (e.index += t.length), { value: t, done: !1 });
        }
      );
    },
    function(t, e, r) {
      var n = r(3),
        i = r(117),
        o = r(4),
        a = r(29),
        s = r(2),
        l = s('iterator'),
        c = s('toStringTag'),
        u = o.values;
      for (var h in i) {
        var d = n[h],
          p = d && d.prototype;
        if (p) {
          if (p[l] !== u)
            try {
              a(p, l, u);
            } catch (t) {
              p[l] = u;
            }
          if ((p[c] || a(p, c, h), i[h]))
            for (var f in o)
              if (p[f] !== o[f])
                try {
                  a(p, f, o[f]);
                } catch (t) {
                  p[f] = o[f];
                }
        }
      }
    },
    function(t, e, r) {
      var n = r(1);
      t.exports = !n(function() {
        return (
          7 !=
          Object.defineProperty({}, 1, {
            get: function() {
              return 7;
            },
          })[1]
        );
      });
    },
    function(t, e, r) {
      var n = r(0),
        i = r(11);
      n({ target: 'Object', stat: !0, forced: !i, sham: !i }, { defineProperty: r(15).f });
    },
    function(t, e, r) {
      var n = r(14);
      t.exports = function(t) {
        if (!n(t)) throw TypeError(String(t) + ' is not an object');
        return t;
      };
    },
    function(t, e) {
      t.exports = function(t) {
        return 'object' == typeof t ? null !== t : 'function' == typeof t;
      };
    },
    function(t, e, r) {
      var n = r(11),
        i = r(104),
        o = r(13),
        a = r(49),
        s = Object.defineProperty;
      e.f = n
        ? s
        : function(t, e, r) {
            if ((o(t), (e = a(e, !0)), o(r), i))
              try {
                return s(t, e, r);
              } catch (t) {}
            if ('get' in r || 'set' in r) throw TypeError('Accessors not supported');
            return 'value' in r && (t[e] = r.value), t;
          };
    },
    function(t, e, r) {
      var n = r(17),
        i = {}.hasOwnProperty;
      t.exports = function(t, e) {
        return i.call(n(t), e);
      };
    },
    function(t, e, r) {
      var n = r(32);
      t.exports = function(t) {
        return Object(n(t));
      };
    },
    function(t, e, r) {
      var n = r(0),
        i = r(116);
      n({ target: 'Array', proto: !0, forced: [].forEach != i }, { forEach: i });
    },
    function(t, e, r) {
      var n = r(3),
        i = r(117),
        o = r(116),
        a = r(29);
      for (var s in i) {
        var l = n[s],
          c = l && l.prototype;
        if (c && c.forEach !== o)
          try {
            a(c, 'forEach', o);
          } catch (t) {
            c.forEach = o;
          }
      }
    },
    function(t, e, r) {
      r(0)({ target: 'Array', stat: !0 }, { isArray: r(58) });
    },
    function(t, e, r) {
      r(0)({ target: 'Object', stat: !0 }, { setPrototypeOf: r(94) });
    },
    function(t, e, r) {
      var n = r(0),
        i = r(1),
        o = r(17),
        a = r(72),
        s = r(122);
      n(
        {
          target: 'Object',
          stat: !0,
          forced: i(function() {
            a(1);
          }),
          sham: !s,
        },
        {
          getPrototypeOf: function(t) {
            return a(o(t));
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(0),
        i = r(45),
        o = r(46),
        a = r(13),
        s = r(14),
        l = r(47),
        c = r(131),
        u = r(1),
        h = i('Reflect', 'construct'),
        d = u(function() {
          function t() {}
          return !(h(function() {}, [], t) instanceof t);
        }),
        p = !u(function() {
          h(function() {});
        }),
        f = d || p;
      n(
        { target: 'Reflect', stat: !0, forced: f, sham: f },
        {
          construct: function(t, e) {
            o(t), a(e);
            var r = arguments.length < 3 ? t : o(arguments[2]);
            if (p && !d) return h(t, e, r);
            if (t == r) {
              switch (e.length) {
                case 0:
                  return new t();
                case 1:
                  return new t(e[0]);
                case 2:
                  return new t(e[0], e[1]);
                case 3:
                  return new t(e[0], e[1], e[2]);
                case 4:
                  return new t(e[0], e[1], e[2], e[3]);
              }
              var n = [null];
              return n.push.apply(n, e), new (c.apply(t, n))();
            }
            var i = r.prototype,
              u = l(s(i) ? i : Object.prototype),
              f = Function.apply.call(t, u, e);
            return s(f) ? f : u;
          },
        }
      );
    },
    function(t, e, r) {
      r(0)({ target: 'Object', stat: !0, sham: !r(11) }, { create: r(47) });
    },
    function(t, e, r) {
      var n = r(53),
        i = r(32);
      t.exports = function(t) {
        return n(i(t));
      };
    },
    function(t, e, r) {
      var n = r(55),
        i = Math.min;
      t.exports = function(t) {
        return t > 0 ? i(n(t), 9007199254740991) : 0;
      };
    },
    function(t, e, r) {
      var n = r(0),
        i = r(73);
      n({ target: 'RegExp', proto: !0, forced: /./.exec !== i }, { exec: i });
    },
    function(t, e, r) {
      var n = r(0),
        i = r(1),
        o = r(25),
        a = r(36).f,
        s = r(11),
        l = i(function() {
          a(1);
        });
      n(
        { target: 'Object', stat: !0, forced: !s || l, sham: !s },
        {
          getOwnPropertyDescriptor: function(t, e) {
            return a(o(t), e);
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(11),
        i = r(15),
        o = r(50);
      t.exports = n
        ? function(t, e, r) {
            return i.f(t, e, o(1, r));
          }
        : function(t, e, r) {
            return (t[e] = r), t;
          };
    },
    function(t, e, r) {
      var n = r(0),
        i = r(14),
        o = r(13),
        a = r(16),
        s = r(36),
        l = r(72);
      n(
        { target: 'Reflect', stat: !0 },
        {
          get: function t(e, r) {
            var n,
              c,
              u = arguments.length < 3 ? e : arguments[2];
            return o(e) === u ? e[r] : (n = s.f(e, r)) ? (a(n, 'value') ? n.value : void 0 === n.get ? void 0 : n.get.call(u)) : i((c = l(e))) ? t(c, r, u) : void 0;
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(3),
        i = r(29),
        o = r(16),
        a = r(80),
        s = r(106),
        l = r(51),
        c = l.get,
        u = l.enforce,
        h = String(String).split('String');
      (t.exports = function(t, e, r, s) {
        var l,
          c = !!s && !!s.unsafe,
          d = !!s && !!s.enumerable,
          p = !!s && !!s.noTargetGet;
        'function' == typeof r && ('string' != typeof e || o(r, 'name') || i(r, 'name', e), (l = u(r)).source || (l.source = h.join('string' == typeof e ? e : ''))),
          t !== n ? (c ? !p && t[e] && (d = !0) : delete t[e], d ? (t[e] = r) : i(t, e, r)) : d ? (t[e] = r) : a(e, r);
      })(Function.prototype, 'toString', function() {
        return ('function' == typeof this && c(this).source) || s(this);
      });
    },
    function(t, e) {
      t.exports = function(t) {
        if (null == t) throw TypeError("Can't call method on " + t);
        return t;
      };
    },
    function(t, e, r) {
      var n = r(0),
        i = r(17),
        o = r(57);
      n(
        {
          target: 'Object',
          stat: !0,
          forced: r(1)(function() {
            o(1);
          }),
        },
        {
          keys: function(t) {
            return o(i(t));
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(0),
        i = r(1),
        o = r(58),
        a = r(14),
        s = r(17),
        l = r(26),
        c = r(59),
        u = r(91),
        h = r(60),
        d = r(2),
        p = r(69),
        f = d('isConcatSpreadable'),
        y =
          p >= 51 ||
          !i(function() {
            var t = [];
            return (t[f] = !1), t.concat()[0] !== t;
          }),
        m = h('concat'),
        v = function(t) {
          if (!a(t)) return !1;
          var e = t[f];
          return void 0 !== e ? !!e : o(t);
        };
      n(
        { target: 'Array', proto: !0, forced: !y || !m },
        {
          concat: function(t) {
            var e,
              r,
              n,
              i,
              o,
              a = s(this),
              h = u(a, 0),
              d = 0;
            for (e = -1, n = arguments.length; e < n; e++)
              if (v((o = -1 === e ? a : arguments[e]))) {
                if (d + (i = l(o.length)) > 9007199254740991) throw TypeError('Maximum allowed index exceeded');
                for (r = 0; r < i; r++, d++) r in o && c(h, d, o[r]);
              } else {
                if (d >= 9007199254740991) throw TypeError('Maximum allowed index exceeded');
                c(h, d++, o);
              }
            return (h.length = d), h;
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(0),
        i = r(14),
        o = r(58),
        a = r(87),
        s = r(26),
        l = r(25),
        c = r(59),
        u = r(2),
        h = r(60)('slice'),
        d = u('species'),
        p = [].slice,
        f = Math.max;
      n(
        { target: 'Array', proto: !0, forced: !h },
        {
          slice: function(t, e) {
            var r,
              n,
              u,
              h = l(this),
              y = s(h.length),
              m = a(t, y),
              v = a(void 0 === e ? y : e, y);
            if (o(h) && ('function' != typeof (r = h.constructor) || (r !== Array && !o(r.prototype)) ? i(r) && null === (r = r[d]) && (r = void 0) : (r = void 0), r === Array || void 0 === r))
              return p.call(h, m, v);
            for (n = new (void 0 === r ? Array : r)(f(v - m, 0)), u = 0; m < v; m++, u++) m in h && c(n, u, h[m]);
            return (n.length = u), n;
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(11),
        i = r(70),
        o = r(50),
        a = r(25),
        s = r(49),
        l = r(16),
        c = r(104),
        u = Object.getOwnPropertyDescriptor;
      e.f = n
        ? u
        : function(t, e) {
            if (((t = a(t)), (e = s(e, !0)), c))
              try {
                return u(t, e);
              } catch (t) {}
            if (l(t, e)) return o(!i.f.call(t, e), t[e]);
          };
    },
    function(t, e, r) {
      var n = r(0),
        i = r(145);
      n(
        {
          target: 'Array',
          stat: !0,
          forced: !r(150)(function(t) {
            Array.from(t);
          }),
        },
        { from: i }
      );
    },
    function(t, e, r) {
      var n = r(11),
        i = r(15).f,
        o = Function.prototype,
        a = o.toString,
        s = /^\s*function ([^ (]*)/;
      n &&
        !('name' in o) &&
        i(o, 'name', {
          configurable: !0,
          get: function() {
            try {
              return a.call(this).match(s)[1];
            } catch (t) {
              return '';
            }
          },
        });
    },
    function(t, e, r) {
      var n = r(0),
        i = r(86).includes,
        o = r(92);
      n(
        { target: 'Array', proto: !0 },
        {
          includes: function(t) {
            return i(this, t, arguments.length > 1 ? arguments[1] : void 0);
          },
        }
      ),
        o('includes');
    },
    function(t, e) {
      var r = {}.toString;
      t.exports = function(t) {
        return r.call(t).slice(8, -1);
      };
    },
    function(t, e, r) {
      var n = r(31),
        i = r(13),
        o = r(1),
        a = r(85),
        s = RegExp.prototype,
        l = s.toString,
        c = o(function() {
          return '/a/b' != l.call({ source: 'a', flags: 'b' });
        }),
        u = 'toString' != l.name;
      (c || u) &&
        n(
          RegExp.prototype,
          'toString',
          function() {
            var t = i(this),
              e = String(t.source),
              r = t.flags;
            return '/' + e + '/' + String(void 0 === r && t instanceof RegExp && !('flags' in s) ? a.call(t) : r);
          },
          { unsafe: !0 }
        );
    },
    function(t, e, r) {
      var n = r(0),
        i = r(137).left,
        o = r(43),
        a = r(69),
        s = r(138);
      n(
        { target: 'Array', proto: !0, forced: !o('reduce') || (!s && a > 79 && a < 83) },
        {
          reduce: function(t) {
            return i(this, t, arguments.length, arguments.length > 1 ? arguments[1] : void 0);
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(1);
      t.exports = function(t, e) {
        var r = [][t];
        return (
          !!r &&
          n(function() {
            r.call(
              null,
              e ||
                function() {
                  throw 1;
                },
              1
            );
          })
        );
      };
    },
    function(t, e, r) {
      var n = r(114),
        i = r(53),
        o = r(17),
        a = r(26),
        s = r(91),
        l = [].push,
        c = function(t) {
          var e = 1 == t,
            r = 2 == t,
            c = 3 == t,
            u = 4 == t,
            h = 6 == t,
            d = 7 == t,
            p = 5 == t || h;
          return function(f, y, m, v) {
            for (var b, g, _ = o(f), w = i(_), k = n(y, m, 3), x = a(w.length), j = 0, O = v || s, E = e ? O(f, x) : r || d ? O(f, 0) : void 0; x > j; j++)
              if ((p || j in w) && ((g = k((b = w[j]), j, _)), t))
                if (e) E[j] = g;
                else if (g)
                  switch (t) {
                    case 3:
                      return !0;
                    case 5:
                      return b;
                    case 6:
                      return j;
                    case 2:
                      l.call(E, b);
                  }
                else
                  switch (t) {
                    case 4:
                      return !1;
                    case 7:
                      l.call(E, b);
                  }
            return h ? -1 : c || u ? u : E;
          };
        };
      t.exports = { forEach: c(0), map: c(1), filter: c(2), some: c(3), every: c(4), find: c(5), findIndex: c(6), filterOut: c(7) };
    },
    function(t, e, r) {
      var n = r(107),
        i = r(3),
        o = function(t) {
          return 'function' == typeof t ? t : void 0;
        };
      t.exports = function(t, e) {
        return arguments.length < 2 ? o(n[t]) || o(i[t]) : (n[t] && n[t][e]) || (i[t] && i[t][e]);
      };
    },
    function(t, e) {
      t.exports = function(t) {
        if ('function' != typeof t) throw TypeError(String(t) + ' is not a function');
        return t;
      };
    },
    function(t, e, r) {
      var n,
        i = r(13),
        o = r(115),
        a = r(88),
        s = r(68),
        l = r(139),
        c = r(105),
        u = r(66),
        h = u('IE_PROTO'),
        d = function() {},
        p = function(t) {
          return '<script>' + t + '</script>';
        },
        f = function() {
          try {
            n = document.domain && new ActiveXObject('htmlfile');
          } catch (t) {}
          var t, e;
          f = n
            ? (function(t) {
                t.write(p('')), t.close();
                var e = t.parentWindow.Object;
                return (t = null), e;
              })(n)
            : (((e = c('iframe')).style.display = 'none'), l.appendChild(e), (e.src = String('javascript:')), (t = e.contentWindow.document).open(), t.write(p('document.F=Object')), t.close(), t.F);
          for (var r = a.length; r--; ) delete f.prototype[a[r]];
          return f();
        };
      (s[h] = !0),
        (t.exports =
          Object.create ||
          function(t, e) {
            var r;
            return null !== t ? ((d.prototype = i(t)), (r = new d()), (d.prototype = null), (r[h] = t)) : (r = f()), void 0 === e ? r : o(r, e);
          });
    },
    function(t, e, r) {
      var n = r(0),
        i = r(128),
        o = r(32);
      n(
        { target: 'String', proto: !0, forced: !r(129)('includes') },
        {
          includes: function(t) {
            return !!~String(o(this)).indexOf(i(t), arguments.length > 1 ? arguments[1] : void 0);
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(14);
      t.exports = function(t, e) {
        if (!n(t)) return t;
        var r, i;
        if (e && 'function' == typeof (r = t.toString) && !n((i = r.call(t)))) return i;
        if ('function' == typeof (r = t.valueOf) && !n((i = r.call(t)))) return i;
        if (!e && 'function' == typeof (r = t.toString) && !n((i = r.call(t)))) return i;
        throw TypeError("Can't convert object to primitive value");
      };
    },
    function(t, e) {
      t.exports = function(t, e) {
        return { enumerable: !(1 & t), configurable: !(2 & t), writable: !(4 & t), value: e };
      };
    },
    function(t, e, r) {
      var n,
        i,
        o,
        a = r(134),
        s = r(3),
        l = r(14),
        c = r(29),
        u = r(16),
        h = r(81),
        d = r(66),
        p = r(68),
        f = s.WeakMap;
      if (a || h.state) {
        var y = h.state || (h.state = new f()),
          m = y.get,
          v = y.has,
          b = y.set;
        (n = function(t, e) {
          if (v.call(y, t)) throw new TypeError('Object already initialized');
          return (e.facade = t), b.call(y, t, e), e;
        }),
          (i = function(t) {
            return m.call(y, t) || {};
          }),
          (o = function(t) {
            return v.call(y, t);
          });
      } else {
        var g = d('state');
        (p[g] = !0),
          (n = function(t, e) {
            if (u(t, g)) throw new TypeError('Object already initialized');
            return (e.facade = t), c(t, g, e), e;
          }),
          (i = function(t) {
            return u(t, g) ? t[g] : {};
          }),
          (o = function(t) {
            return u(t, g);
          });
      }
      t.exports = {
        set: n,
        get: i,
        has: o,
        enforce: function(t) {
          return o(t) ? i(t) : n(t, {});
        },
        getterFor: function(t) {
          return function(e) {
            var r;
            if (!l(e) || (r = i(e)).type !== t) throw TypeError('Incompatible receiver, ' + t + ' required');
            return r;
          };
        },
      };
    },
    function(t, e) {
      t.exports = !1;
    },
    function(t, e, r) {
      var n = r(1),
        i = r(40),
        o = ''.split;
      t.exports = n(function() {
        return !Object('z').propertyIsEnumerable(0);
      })
        ? function(t) {
            return 'String' == i(t) ? o.call(t, '') : Object(t);
          }
        : Object;
    },
    function(t, e, r) {
      var n = r(112),
        i = r(88).concat('length', 'prototype');
      e.f =
        Object.getOwnPropertyNames ||
        function(t) {
          return n(t, i);
        };
    },
    function(t, e) {
      var r = Math.ceil,
        n = Math.floor;
      t.exports = function(t) {
        return isNaN((t = +t)) ? 0 : (t > 0 ? n : r)(t);
      };
    },
    function(t, e, r) {
      var n = r(0),
        i = r(113).values;
      n(
        { target: 'Object', stat: !0 },
        {
          values: function(t) {
            return i(t);
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(112),
        i = r(88);
      t.exports =
        Object.keys ||
        function(t) {
          return n(t, i);
        };
    },
    function(t, e, r) {
      var n = r(40);
      t.exports =
        Array.isArray ||
        function(t) {
          return 'Array' == n(t);
        };
    },
    function(t, e, r) {
      var n = r(49),
        i = r(15),
        o = r(50);
      t.exports = function(t, e, r) {
        var a = n(e);
        a in t ? i.f(t, a, o(0, r)) : (t[a] = r);
      };
    },
    function(t, e, r) {
      var n = r(1),
        i = r(2),
        o = r(69),
        a = i('species');
      t.exports = function(t) {
        return (
          o >= 51 ||
          !n(function() {
            var e = [];
            return (
              ((e.constructor = {})[a] = function() {
                return { foo: 1 };
              }),
              1 !== e[t](Boolean).foo
            );
          })
        );
      };
    },
    function(t, e) {
      t.exports = {};
    },
    function(t, e, r) {
      var n = r(0),
        i = r(113).entries;
      n(
        { target: 'Object', stat: !0 },
        {
          entries: function(t) {
            return i(t);
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(96),
        i = r(13),
        o = r(26),
        a = r(32),
        s = r(97),
        l = r(98);
      n('match', 1, function(t, e, r) {
        return [
          function(e) {
            var r = a(this),
              n = null == e ? void 0 : e[t];
            return void 0 !== n ? n.call(e, r) : new RegExp(e)[t](String(r));
          },
          function(t) {
            var n = r(e, t, this);
            if (n.done) return n.value;
            var a = i(t),
              c = String(this);
            if (!a.global) return l(a, c);
            var u = a.unicode;
            a.lastIndex = 0;
            for (var h, d = [], p = 0; null !== (h = l(a, c)); ) {
              var f = String(h[0]);
              (d[p] = f), '' === f && (a.lastIndex = s(c, o(a.lastIndex), u)), p++;
            }
            return 0 === p ? null : d;
          },
        ];
      });
    },
    function(t, e, r) {
      var n = r(0),
        i = r(53),
        o = r(25),
        a = r(43),
        s = [].join,
        l = i != Object,
        c = a('join', ',');
      n(
        { target: 'Array', proto: !0, forced: l || !c },
        {
          join: function(t) {
            return s.call(o(this), void 0 === t ? ',' : t);
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(96),
        i = r(99),
        o = r(13),
        a = r(32),
        s = r(155),
        l = r(97),
        c = r(26),
        u = r(98),
        h = r(73),
        d = r(95).UNSUPPORTED_Y,
        p = [].push,
        f = Math.min;
      n(
        'split',
        2,
        function(t, e, r) {
          var n;
          return (
            (n =
              'c' == 'abbc'.split(/(b)*/)[1] ||
              4 != 'test'.split(/(?:)/, -1).length ||
              2 != 'ab'.split(/(?:ab)*/).length ||
              4 != '.'.split(/(.?)(.?)/).length ||
              '.'.split(/()()/).length > 1 ||
              ''.split(/.?/).length
                ? function(t, r) {
                    var n = String(a(this)),
                      o = void 0 === r ? 4294967295 : r >>> 0;
                    if (0 === o) return [];
                    if (void 0 === t) return [n];
                    if (!i(t)) return e.call(n, t, o);
                    for (
                      var s, l, c, u = [], d = (t.ignoreCase ? 'i' : '') + (t.multiline ? 'm' : '') + (t.unicode ? 'u' : '') + (t.sticky ? 'y' : ''), f = 0, y = new RegExp(t.source, d + 'g');
                      (s = h.call(y, n)) &&
                      !((l = y.lastIndex) > f && (u.push(n.slice(f, s.index)), s.length > 1 && s.index < n.length && p.apply(u, s.slice(1)), (c = s[0].length), (f = l), u.length >= o));

                    )
                      y.lastIndex === s.index && y.lastIndex++;
                    return f === n.length ? (!c && y.test('')) || u.push('') : u.push(n.slice(f)), u.length > o ? u.slice(0, o) : u;
                  }
                : '0'.split(void 0, 0).length
                ? function(t, r) {
                    return void 0 === t && 0 === r ? [] : e.call(this, t, r);
                  }
                : e),
            [
              function(e, r) {
                var i = a(this),
                  o = null == e ? void 0 : e[t];
                return void 0 !== o ? o.call(e, i, r) : n.call(String(i), e, r);
              },
              function(t, i) {
                var a = r(n, t, this, i, n !== e);
                if (a.done) return a.value;
                var h = o(t),
                  p = String(this),
                  y = s(h, RegExp),
                  m = h.unicode,
                  v = (h.ignoreCase ? 'i' : '') + (h.multiline ? 'm' : '') + (h.unicode ? 'u' : '') + (d ? 'g' : 'y'),
                  b = new y(d ? '^(?:' + h.source + ')' : h, v),
                  g = void 0 === i ? 4294967295 : i >>> 0;
                if (0 === g) return [];
                if (0 === p.length) return null === u(b, p) ? [p] : [];
                for (var _ = 0, w = 0, k = []; w < p.length; ) {
                  b.lastIndex = d ? 0 : w;
                  var x,
                    j = u(b, d ? p.slice(w) : p);
                  if (null === j || (x = f(c(b.lastIndex + (d ? w : 0)), p.length)) === _) w = l(p, w, m);
                  else {
                    if ((k.push(p.slice(_, w)), k.length === g)) return k;
                    for (var O = 1; O <= j.length - 1; O++) if ((k.push(j[O]), k.length === g)) return k;
                    w = _ = x;
                  }
                }
                return k.push(p.slice(_)), k;
              },
            ]
          );
        },
        d
      );
    },
    function(t, e, r) {
      var n = r(67),
        i = r(82),
        o = n('keys');
      t.exports = function(t) {
        return o[t] || (o[t] = i(t));
      };
    },
    function(t, e, r) {
      var n = r(52),
        i = r(81);
      (t.exports = function(t, e) {
        return i[t] || (i[t] = void 0 !== e ? e : {});
      })('versions', []).push({ version: '3.12.1', mode: n ? 'pure' : 'global', copyright: '© 2021 Denis Pushkarev (zloirock.ru)' });
    },
    function(t, e) {
      t.exports = {};
    },
    function(t, e, r) {
      var n,
        i,
        o = r(3),
        a = r(135),
        s = o.process,
        l = s && s.versions,
        c = l && l.v8;
      c ? (i = (n = c.split('.'))[0] < 4 ? 1 : n[0] + n[1]) : a && (!(n = a.match(/Edge\/(\d+)/)) || n[1] >= 74) && (n = a.match(/Chrome\/(\d+)/)) && (i = n[1]), (t.exports = i && +i);
    },
    function(t, e, r) {
      var n = {}.propertyIsEnumerable,
        i = Object.getOwnPropertyDescriptor,
        o = i && !n.call({ 1: 2 }, 1);
      e.f = o
        ? function(t) {
            var e = i(this, t);
            return !!e && e.enumerable;
          }
        : n;
    },
    function(t, e, r) {
      var n = r(0),
        i = r(44).find,
        o = r(92),
        a = !0;
      'find' in [] &&
        Array(1).find(function() {
          a = !1;
        }),
        n(
          { target: 'Array', proto: !0, forced: a },
          {
            find: function(t) {
              return i(this, t, arguments.length > 1 ? arguments[1] : void 0);
            },
          }
        ),
        o('find');
    },
    function(t, e, r) {
      var n = r(16),
        i = r(17),
        o = r(66),
        a = r(122),
        s = o('IE_PROTO'),
        l = Object.prototype;
      t.exports = a
        ? Object.getPrototypeOf
        : function(t) {
            return (t = i(t)), n(t, s) ? t[s] : 'function' == typeof t.constructor && t instanceof t.constructor ? t.constructor.prototype : t instanceof Object ? l : null;
          };
    },
    function(t, e, r) {
      var n,
        i,
        o = r(85),
        a = r(95),
        s = r(67),
        l = RegExp.prototype.exec,
        c = s('native-string-replace', String.prototype.replace),
        u = l,
        h = ((n = /a/), (i = /b*/g), l.call(n, 'a'), l.call(i, 'a'), 0 !== n.lastIndex || 0 !== i.lastIndex),
        d = a.UNSUPPORTED_Y || a.BROKEN_CARET,
        p = void 0 !== /()??/.exec('')[1];
      (h || p || d) &&
        (u = function(t) {
          var e,
            r,
            n,
            i,
            a = this,
            s = d && a.sticky,
            u = o.call(a),
            f = a.source,
            y = 0,
            m = t;
          return (
            s &&
              (-1 === (u = u.replace('y', '')).indexOf('g') && (u += 'g'),
              (m = String(t).slice(a.lastIndex)),
              a.lastIndex > 0 && (!a.multiline || (a.multiline && '\n' !== t[a.lastIndex - 1])) && ((f = '(?: ' + f + ')'), (m = ' ' + m), y++),
              (r = new RegExp('^(?:' + f + ')', u))),
            p && (r = new RegExp('^' + f + '$(?!\\s)', u)),
            h && (e = a.lastIndex),
            (n = l.call(s ? r : a, m)),
            s
              ? n
                ? ((n.input = n.input.slice(y)), (n[0] = n[0].slice(y)), (n.index = a.lastIndex), (a.lastIndex += n[0].length))
                : (a.lastIndex = 0)
              : h && n && (a.lastIndex = a.global ? n.index + n[0].length : e),
            p &&
              n &&
              n.length > 1 &&
              c.call(n[0], r, function() {
                for (i = 1; i < arguments.length - 2; i++) void 0 === arguments[i] && (n[i] = void 0);
              }),
            n
          );
        }),
        (t.exports = u);
    },
    function(t, e, r) {
      var n = r(96),
        i = r(13),
        o = r(26),
        a = r(55),
        s = r(32),
        l = r(97),
        c = r(151),
        u = r(98),
        h = Math.max,
        d = Math.min;
      n('replace', 2, function(t, e, r, n) {
        var p = n.REGEXP_REPLACE_SUBSTITUTES_UNDEFINED_CAPTURE,
          f = n.REPLACE_KEEPS_$0,
          y = p ? '$' : '$0';
        return [
          function(r, n) {
            var i = s(this),
              o = null == r ? void 0 : r[t];
            return void 0 !== o ? o.call(r, i, n) : e.call(String(i), r, n);
          },
          function(t, n) {
            if ((!p && f) || ('string' == typeof n && -1 === n.indexOf(y))) {
              var s = r(e, t, this, n);
              if (s.done) return s.value;
            }
            var m = i(t),
              v = String(this),
              b = 'function' == typeof n;
            b || (n = String(n));
            var g = m.global;
            if (g) {
              var _ = m.unicode;
              m.lastIndex = 0;
            }
            for (var w = []; ; ) {
              var k = u(m, v);
              if (null === k) break;
              if ((w.push(k), !g)) break;
              '' === String(k[0]) && (m.lastIndex = l(v, o(m.lastIndex), _));
            }
            for (var x, j = '', O = 0, E = 0; E < w.length; E++) {
              k = w[E];
              for (var C = String(k[0]), S = h(d(a(k.index), v.length), 0), A = [], P = 1; P < k.length; P++) A.push(void 0 === (x = k[P]) ? x : String(x));
              var T = k.groups;
              if (b) {
                var R = [C].concat(A, S, v);
                void 0 !== T && R.push(T);
                var I = String(n.apply(void 0, R));
              } else I = c(C, v, S, A, T, n);
              S >= O && ((j += v.slice(O, S) + I), (O = S + C.length));
            }
            return j + v.slice(O);
          },
        ];
      });
    },
    function(t, e, r) {
      var n = r(11),
        i = r(3),
        o = r(90),
        a = r(124),
        s = r(15).f,
        l = r(54).f,
        c = r(99),
        u = r(85),
        h = r(95),
        d = r(31),
        p = r(1),
        f = r(51).enforce,
        y = r(152),
        m = r(2)('match'),
        v = i.RegExp,
        b = v.prototype,
        g = /a/g,
        _ = /a/g,
        w = new v(g) !== g,
        k = h.UNSUPPORTED_Y;
      if (
        n &&
        o(
          'RegExp',
          !w ||
            k ||
            p(function() {
              return (_[m] = !1), v(g) != g || v(_) == _ || '/a/i' != v(g, 'i');
            })
        )
      ) {
        for (
          var x = function(t, e) {
              var r,
                n = this instanceof x,
                i = c(t),
                o = void 0 === e;
              if (!n && i && t.constructor === x && o) return t;
              w ? i && !o && (t = t.source) : t instanceof x && (o && (e = u.call(t)), (t = t.source)), k && (r = !!e && e.indexOf('y') > -1) && (e = e.replace(/y/g, ''));
              var s = a(w ? new v(t, e) : v(t, e), n ? this : b, x);
              k && r && (f(s).sticky = !0);
              return s;
            },
            j = function(t) {
              (t in x) ||
                s(x, t, {
                  configurable: !0,
                  get: function() {
                    return v[t];
                  },
                  set: function(e) {
                    v[t] = e;
                  },
                });
            },
            O = l(v),
            E = 0;
          O.length > E;

        )
          j(O[E++]);
        (b.constructor = x), (x.prototype = b), d(i, 'RegExp', x);
      }
      y('RegExp');
    },
    function(t, e, r) {
      var n = r(0),
        i = r(44).some;
      n(
        { target: 'Array', proto: !0, forced: !r(43)('some') },
        {
          some: function(t) {
            return i(this, t, arguments.length > 1 ? arguments[1] : void 0);
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(0),
        i = r(44).map;
      n(
        { target: 'Array', proto: !0, forced: !r(60)('map') },
        {
          map: function(t) {
            return i(this, t, arguments.length > 1 ? arguments[1] : void 0);
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(0),
        i = r(44).filter;
      n(
        { target: 'Array', proto: !0, forced: !r(60)('filter') },
        {
          filter: function(t) {
            return i(this, t, arguments.length > 1 ? arguments[1] : void 0);
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(31),
        i = Date.prototype,
        o = i.toString,
        a = i.getTime;
      new Date(NaN) + '' != 'Invalid Date' &&
        n(i, 'toString', function() {
          var t = a.call(this);
          return t == t ? o.call(this) : 'Invalid Date';
        });
    },
    function(t, e, r) {
      var n = r(3),
        i = r(29);
      t.exports = function(t, e) {
        try {
          i(n, t, e);
        } catch (r) {
          n[t] = e;
        }
        return e;
      };
    },
    function(t, e, r) {
      var n = r(3),
        i = r(80),
        o = n['__core-js_shared__'] || i('__core-js_shared__', {});
      t.exports = o;
    },
    function(t, e) {
      var r = 0,
        n = Math.random();
      t.exports = function(t) {
        return 'Symbol(' + String(void 0 === t ? '' : t) + ')_' + (++r + n).toString(36);
      };
    },
    function(t, e, r) {
      var n = {};
      (n[r(2)('toStringTag')] = 'z'), (t.exports = '[object z]' === String(n));
    },
    function(t, e, r) {
      var n = r(69),
        i = r(1);
      t.exports =
        !!Object.getOwnPropertySymbols &&
        !i(function() {
          return !String(Symbol()) || (!Symbol.sham && n && n < 41);
        });
    },
    function(t, e, r) {
      var n = r(13);
      t.exports = function() {
        var t = n(this),
          e = '';
        return t.global && (e += 'g'), t.ignoreCase && (e += 'i'), t.multiline && (e += 'm'), t.dotAll && (e += 's'), t.unicode && (e += 'u'), t.sticky && (e += 'y'), e;
      };
    },
    function(t, e, r) {
      var n = r(25),
        i = r(26),
        o = r(87),
        a = function(t) {
          return function(e, r, a) {
            var s,
              l = n(e),
              c = i(l.length),
              u = o(a, c);
            if (t && r != r) {
              for (; c > u; ) if ((s = l[u++]) != s) return !0;
            } else for (; c > u; u++) if ((t || u in l) && l[u] === r) return t || u || 0;
            return !t && -1;
          };
        };
      t.exports = { includes: a(!0), indexOf: a(!1) };
    },
    function(t, e, r) {
      var n = r(55),
        i = Math.max,
        o = Math.min;
      t.exports = function(t, e) {
        var r = n(t);
        return r < 0 ? i(r + e, 0) : o(r, e);
      };
    },
    function(t, e) {
      t.exports = ['constructor', 'hasOwnProperty', 'isPrototypeOf', 'propertyIsEnumerable', 'toLocaleString', 'toString', 'valueOf'];
    },
    function(t, e) {
      e.f = Object.getOwnPropertySymbols;
    },
    function(t, e, r) {
      var n = r(1),
        i = /#|\.prototype\./,
        o = function(t, e) {
          var r = s[a(t)];
          return r == c || (r != l && ('function' == typeof e ? n(e) : !!e));
        },
        a = (o.normalize = function(t) {
          return String(t)
            .replace(i, '.')
            .toLowerCase();
        }),
        s = (o.data = {}),
        l = (o.NATIVE = 'N'),
        c = (o.POLYFILL = 'P');
      t.exports = o;
    },
    function(t, e, r) {
      var n = r(14),
        i = r(58),
        o = r(2)('species');
      t.exports = function(t, e) {
        var r;
        return (
          i(t) && ('function' != typeof (r = t.constructor) || (r !== Array && !i(r.prototype)) ? n(r) && null === (r = r[o]) && (r = void 0) : (r = void 0)),
          new (void 0 === r ? Array : r)(0 === e ? 0 : e)
        );
      };
    },
    function(t, e, r) {
      var n = r(2),
        i = r(47),
        o = r(15),
        a = n('unscopables'),
        s = Array.prototype;
      null == s[a] && o.f(s, a, { configurable: !0, value: i(null) }),
        (t.exports = function(t) {
          s[a][t] = !0;
        });
    },
    function(t, e, r) {
      var n = r(15).f,
        i = r(16),
        o = r(2)('toStringTag');
      t.exports = function(t, e, r) {
        t && !i((t = r ? t : t.prototype), o) && n(t, o, { configurable: !0, value: e });
      };
    },
    function(t, e, r) {
      var n = r(13),
        i = r(144);
      t.exports =
        Object.setPrototypeOf ||
        ('__proto__' in {}
          ? (function() {
              var t,
                e = !1,
                r = {};
              try {
                (t = Object.getOwnPropertyDescriptor(Object.prototype, '__proto__').set).call(r, []), (e = r instanceof Array);
              } catch (t) {}
              return function(r, o) {
                return n(r), i(o), e ? t.call(r, o) : (r.__proto__ = o), r;
              };
            })()
          : void 0);
    },
    function(t, e, r) {
      var n = r(1);
      function i(t, e) {
        return RegExp(t, e);
      }
      (e.UNSUPPORTED_Y = n(function() {
        var t = i('a', 'y');
        return (t.lastIndex = 2), null != t.exec('abcd');
      })),
        (e.BROKEN_CARET = n(function() {
          var t = i('^r', 'gy');
          return (t.lastIndex = 2), null != t.exec('str');
        }));
    },
    function(t, e, r) {
      r(27);
      var n = r(31),
        i = r(73),
        o = r(1),
        a = r(2),
        s = r(29),
        l = a('species'),
        c = RegExp.prototype,
        u = !o(function() {
          var t = /./;
          return (
            (t.exec = function() {
              var t = [];
              return (t.groups = { a: '7' }), t;
            }),
            '7' !== ''.replace(t, '$<a>')
          );
        }),
        h = '$0' === 'a'.replace(/./, '$0'),
        d = a('replace'),
        p = !!/./[d] && '' === /./[d]('a', '$0'),
        f = !o(function() {
          var t = /(?:)/,
            e = t.exec;
          t.exec = function() {
            return e.apply(this, arguments);
          };
          var r = 'ab'.split(t);
          return 2 !== r.length || 'a' !== r[0] || 'b' !== r[1];
        });
      t.exports = function(t, e, r, d) {
        var y = a(t),
          m = !o(function() {
            var e = {};
            return (
              (e[y] = function() {
                return 7;
              }),
              7 != ''[t](e)
            );
          }),
          v =
            m &&
            !o(function() {
              var e = !1,
                r = /a/;
              return (
                'split' === t &&
                  (((r = {}).constructor = {}),
                  (r.constructor[l] = function() {
                    return r;
                  }),
                  (r.flags = ''),
                  (r[y] = /./[y])),
                (r.exec = function() {
                  return (e = !0), null;
                }),
                r[y](''),
                !e
              );
            });
        if (!m || !v || ('replace' === t && (!u || !h || p)) || ('split' === t && !f)) {
          var b = /./[y],
            g = r(
              y,
              ''[t],
              function(t, e, r, n, o) {
                var a = e.exec;
                return a === i || a === c.exec ? (m && !o ? { done: !0, value: b.call(e, r, n) } : { done: !0, value: t.call(r, e, n) }) : { done: !1 };
              },
              { REPLACE_KEEPS_$0: h, REGEXP_REPLACE_SUBSTITUTES_UNDEFINED_CAPTURE: p }
            ),
            _ = g[0],
            w = g[1];
          n(String.prototype, t, _),
            n(
              c,
              y,
              2 == e
                ? function(t, e) {
                    return w.call(t, this, e);
                  }
                : function(t) {
                    return w.call(t, this);
                  }
            );
        }
        d && s(c[y], 'sham', !0);
      };
    },
    function(t, e, r) {
      var n = r(123).charAt;
      t.exports = function(t, e, r) {
        return e + (r ? n(t, e).length : 1);
      };
    },
    function(t, e, r) {
      var n = r(40),
        i = r(73);
      t.exports = function(t, e) {
        var r = t.exec;
        if ('function' == typeof r) {
          var o = r.call(t, e);
          if ('object' != typeof o) throw TypeError('RegExp exec method returned something other than an Object or null');
          return o;
        }
        if ('RegExp' !== n(t)) throw TypeError('RegExp#exec called on incompatible receiver');
        return i.call(t, e);
      };
    },
    function(t, e, r) {
      var n = r(14),
        i = r(40),
        o = r(2)('match');
      t.exports = function(t) {
        var e;
        return n(t) && (void 0 !== (e = t[o]) ? !!e : 'RegExp' == i(t));
      };
    },
    function(t, e, r) {
      var n = r(0),
        i = r(154);
      n({ global: !0, forced: parseInt != i }, { parseInt: i });
    },
    function(t, e, r) {
      var n = r(32),
        i = '[' + r(102) + ']',
        o = RegExp('^' + i + i + '*'),
        a = RegExp(i + i + '*$'),
        s = function(t) {
          return function(e) {
            var r = String(n(e));
            return 1 & t && (r = r.replace(o, '')), 2 & t && (r = r.replace(a, '')), r;
          };
        };
      t.exports = { start: s(1), end: s(2), trim: s(3) };
    },
    function(t, e) {
      t.exports = '\t\n\v\f\r                　\u2028\u2029\ufeff';
    },
    function(t, e, r) {
      var n,
        i = r(0),
        o = r(36).f,
        a = r(26),
        s = r(128),
        l = r(32),
        c = r(129),
        u = r(52),
        h = ''.startsWith,
        d = Math.min,
        p = c('startsWith');
      i(
        { target: 'String', proto: !0, forced: !!(u || p || ((n = o(String.prototype, 'startsWith')), !n || n.writable)) && !p },
        {
          startsWith: function(t) {
            var e = String(l(this));
            s(t);
            var r = a(d(arguments.length > 1 ? arguments[1] : void 0, e.length)),
              n = String(t);
            return h ? h.call(e, n, r) : e.slice(r, r + n.length) === n;
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(11),
        i = r(1),
        o = r(105);
      t.exports =
        !n &&
        !i(function() {
          return (
            7 !=
            Object.defineProperty(o('div'), 'a', {
              get: function() {
                return 7;
              },
            }).a
          );
        });
    },
    function(t, e, r) {
      var n = r(3),
        i = r(14),
        o = n.document,
        a = i(o) && i(o.createElement);
      t.exports = function(t) {
        return a ? o.createElement(t) : {};
      };
    },
    function(t, e, r) {
      var n = r(81),
        i = Function.toString;
      'function' != typeof n.inspectSource &&
        (n.inspectSource = function(t) {
          return i.call(t);
        }),
        (t.exports = n.inspectSource);
    },
    function(t, e, r) {
      var n = r(3);
      t.exports = n;
    },
    function(t, e, r) {
      var n = r(84);
      t.exports = n && !Symbol.sham && 'symbol' == typeof Symbol.iterator;
    },
    function(t, e, r) {
      var n = r(83),
        i = r(40),
        o = r(2)('toStringTag'),
        a =
          'Arguments' ==
          i(
            (function() {
              return arguments;
            })()
          );
      t.exports = n
        ? i
        : function(t) {
            var e, r, n;
            return void 0 === t
              ? 'Undefined'
              : null === t
              ? 'Null'
              : 'string' ==
                typeof (r = (function(t, e) {
                  try {
                    return t[e];
                  } catch (t) {}
                })((e = Object(t)), o))
              ? r
              : a
              ? i(e)
              : 'Object' == (n = i(e)) && 'function' == typeof e.callee
              ? 'Arguments'
              : n;
          };
    },
    function(t, e, r) {
      var n = r(16),
        i = r(111),
        o = r(36),
        a = r(15);
      t.exports = function(t, e) {
        for (var r = i(e), s = a.f, l = o.f, c = 0; c < r.length; c++) {
          var u = r[c];
          n(t, u) || s(t, u, l(e, u));
        }
      };
    },
    function(t, e, r) {
      var n = r(45),
        i = r(54),
        o = r(89),
        a = r(13);
      t.exports =
        n('Reflect', 'ownKeys') ||
        function(t) {
          var e = i.f(a(t)),
            r = o.f;
          return r ? e.concat(r(t)) : e;
        };
    },
    function(t, e, r) {
      var n = r(16),
        i = r(25),
        o = r(86).indexOf,
        a = r(68);
      t.exports = function(t, e) {
        var r,
          s = i(t),
          l = 0,
          c = [];
        for (r in s) !n(a, r) && n(s, r) && c.push(r);
        for (; e.length > l; ) n(s, (r = e[l++])) && (~o(c, r) || c.push(r));
        return c;
      };
    },
    function(t, e, r) {
      var n = r(11),
        i = r(57),
        o = r(25),
        a = r(70).f,
        s = function(t) {
          return function(e) {
            for (var r, s = o(e), l = i(s), c = l.length, u = 0, h = []; c > u; ) (r = l[u++]), (n && !a.call(s, r)) || h.push(t ? [r, s[r]] : s[r]);
            return h;
          };
        };
      t.exports = { entries: s(!0), values: s(!1) };
    },
    function(t, e, r) {
      var n = r(46);
      t.exports = function(t, e, r) {
        if ((n(t), void 0 === e)) return t;
        switch (r) {
          case 0:
            return function() {
              return t.call(e);
            };
          case 1:
            return function(r) {
              return t.call(e, r);
            };
          case 2:
            return function(r, n) {
              return t.call(e, r, n);
            };
          case 3:
            return function(r, n, i) {
              return t.call(e, r, n, i);
            };
        }
        return function() {
          return t.apply(e, arguments);
        };
      };
    },
    function(t, e, r) {
      var n = r(11),
        i = r(15),
        o = r(13),
        a = r(57);
      t.exports = n
        ? Object.defineProperties
        : function(t, e) {
            o(t);
            for (var r, n = a(e), s = n.length, l = 0; s > l; ) i.f(t, (r = n[l++]), e[r]);
            return t;
          };
    },
    function(t, e, r) {
      var n = r(44).forEach,
        i = r(43)('forEach');
      t.exports = i
        ? [].forEach
        : function(t) {
            return n(this, t, arguments.length > 1 ? arguments[1] : void 0);
          };
    },
    function(t, e) {
      t.exports = {
        CSSRuleList: 0,
        CSSStyleDeclaration: 0,
        CSSValueList: 0,
        ClientRectList: 0,
        DOMRectList: 0,
        DOMStringList: 0,
        DOMTokenList: 1,
        DataTransferItemList: 0,
        FileList: 0,
        HTMLAllCollection: 0,
        HTMLCollection: 0,
        HTMLFormElement: 0,
        HTMLSelectElement: 0,
        MediaList: 0,
        MimeTypeArray: 0,
        NamedNodeMap: 0,
        NodeList: 1,
        PaintRequestList: 0,
        Plugin: 0,
        PluginArray: 0,
        SVGLengthList: 0,
        SVGNumberList: 0,
        SVGPathSegList: 0,
        SVGPointList: 0,
        SVGStringList: 0,
        SVGTransformList: 0,
        SourceBufferList: 0,
        StyleSheetList: 0,
        TextTrackCueList: 0,
        TextTrackList: 0,
        TouchList: 0,
      };
    },
    function(t, e, r) {
      var n = r(2);
      e.f = n;
    },
    function(t, e, r) {
      var n = r(107),
        i = r(16),
        o = r(118),
        a = r(15).f;
      t.exports = function(t) {
        var e = n.Symbol || (n.Symbol = {});
        i(e, t) || a(e, t, { value: o.f(t) });
      };
    },
    function(t, e, r) {
      var n = r(0),
        i = r(143),
        o = r(72),
        a = r(94),
        s = r(93),
        l = r(29),
        c = r(31),
        u = r(2),
        h = r(52),
        d = r(61),
        p = r(121),
        f = p.IteratorPrototype,
        y = p.BUGGY_SAFARI_ITERATORS,
        m = u('iterator'),
        v = function() {
          return this;
        };
      t.exports = function(t, e, r, u, p, b, g) {
        i(r, e, u);
        var _,
          w,
          k,
          x = function(t) {
            if (t === p && S) return S;
            if (!y && t in E) return E[t];
            switch (t) {
              case 'keys':
              case 'values':
              case 'entries':
                return function() {
                  return new r(this, t);
                };
            }
            return function() {
              return new r(this);
            };
          },
          j = e + ' Iterator',
          O = !1,
          E = t.prototype,
          C = E[m] || E['@@iterator'] || (p && E[p]),
          S = (!y && C) || x(p),
          A = ('Array' == e && E.entries) || C;
        if (
          (A && ((_ = o(A.call(new t()))), f !== Object.prototype && _.next && (h || o(_) === f || (a ? a(_, f) : 'function' != typeof _[m] && l(_, m, v)), s(_, j, !0, !0), h && (d[j] = v))),
          'values' == p &&
            C &&
            'values' !== C.name &&
            ((O = !0),
            (S = function() {
              return C.call(this);
            })),
          (h && !g) || E[m] === S || l(E, m, S),
          (d[e] = S),
          p)
        )
          if (((w = { values: x('values'), keys: b ? S : x('keys'), entries: x('entries') }), g)) for (k in w) (y || O || !(k in E)) && c(E, k, w[k]);
          else n({ target: e, proto: !0, forced: y || O }, w);
        return w;
      };
    },
    function(t, e, r) {
      var n,
        i,
        o,
        a = r(1),
        s = r(72),
        l = r(29),
        c = r(16),
        u = r(2),
        h = r(52),
        d = u('iterator'),
        p = !1;
      [].keys && ('next' in (o = [].keys()) ? (i = s(s(o))) !== Object.prototype && (n = i) : (p = !0));
      var f =
        null == n ||
        a(function() {
          var t = {};
          return n[d].call(t) !== t;
        });
      f && (n = {}),
        (h && !f) ||
          c(n, d) ||
          l(n, d, function() {
            return this;
          }),
        (t.exports = { IteratorPrototype: n, BUGGY_SAFARI_ITERATORS: p });
    },
    function(t, e, r) {
      var n = r(1);
      t.exports = !n(function() {
        function t() {}
        return (t.prototype.constructor = null), Object.getPrototypeOf(new t()) !== t.prototype;
      });
    },
    function(t, e, r) {
      var n = r(55),
        i = r(32),
        o = function(t) {
          return function(e, r) {
            var o,
              a,
              s = String(i(e)),
              l = n(r),
              c = s.length;
            return l < 0 || l >= c
              ? t
                ? ''
                : void 0
              : (o = s.charCodeAt(l)) < 55296 || o > 56319 || l + 1 === c || (a = s.charCodeAt(l + 1)) < 56320 || a > 57343
              ? t
                ? s.charAt(l)
                : o
              : t
              ? s.slice(l, l + 2)
              : a - 56320 + ((o - 55296) << 10) + 65536;
          };
        };
      t.exports = { codeAt: o(!1), charAt: o(!0) };
    },
    function(t, e, r) {
      var n = r(14),
        i = r(94);
      t.exports = function(t, e, r) {
        var o, a;
        return i && 'function' == typeof (o = e.constructor) && o !== r && n((a = o.prototype)) && a !== r.prototype && i(t, a), t;
      };
    },
    function(t, e, r) {
      var n = r(0),
        i = r(11),
        o = r(111),
        a = r(25),
        s = r(36),
        l = r(59);
      n(
        { target: 'Object', stat: !0, sham: !i },
        {
          getOwnPropertyDescriptors: function(t) {
            for (var e, r, n = a(t), i = s.f, c = o(n), u = {}, h = 0; c.length > h; ) void 0 !== (r = i(n, (e = c[h++]))) && l(u, e, r);
            return u;
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(0),
        i = r(11);
      n({ target: 'Object', stat: !0, forced: !i, sham: !i }, { defineProperties: r(115) });
    },
    function(t, e, r) {
      var n = r(0),
        i = r(156);
      n({ global: !0, forced: parseFloat != i }, { parseFloat: i });
    },
    function(t, e, r) {
      var n = r(99);
      t.exports = function(t) {
        if (n(t)) throw TypeError("The method doesn't accept regular expressions");
        return t;
      };
    },
    function(t, e, r) {
      var n = r(2)('match');
      t.exports = function(t) {
        var e = /./;
        try {
          '/./'[t](e);
        } catch (r) {
          try {
            return (e[n] = !1), '/./'[t](e);
          } catch (t) {}
        }
        return !1;
      };
    },
    function(t, e, r) {
      var n = r(0),
        i = r(86).indexOf,
        o = r(43),
        a = [].indexOf,
        s = !!a && 1 / [1].indexOf(1, -0) < 0,
        l = o('indexOf');
      n(
        { target: 'Array', proto: !0, forced: s || !l },
        {
          indexOf: function(t) {
            return s ? a.apply(this, arguments) || 0 : i(this, t, arguments.length > 1 ? arguments[1] : void 0);
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(46),
        i = r(14),
        o = [].slice,
        a = {},
        s = function(t, e, r) {
          if (!(e in a)) {
            for (var n = [], i = 0; i < e; i++) n[i] = 'a[' + i + ']';
            a[e] = Function('C,a', 'return new C(' + n.join(',') + ')');
          }
          return a[e](t, r);
        };
      t.exports =
        Function.bind ||
        function(t) {
          var e = n(this),
            r = o.call(arguments, 1),
            a = function() {
              var n = r.concat(o.call(arguments));
              return this instanceof a ? s(e, n.length, n) : e.apply(t, n);
            };
          return i(e.prototype) && (a.prototype = e.prototype), a;
        };
    },
    function(t, e, r) {
      r(0)({ target: 'Function', proto: !0 }, { bind: r(131) });
    },
    function(t, e) {
      var r;
      r = (function() {
        return this;
      })();
      try {
        r = r || new Function('return this')();
      } catch (t) {
        'object' == typeof window && (r = window);
      }
      t.exports = r;
    },
    function(t, e, r) {
      var n = r(3),
        i = r(106),
        o = n.WeakMap;
      t.exports = 'function' == typeof o && /native code/.test(i(o));
    },
    function(t, e, r) {
      var n = r(45);
      t.exports = n('navigator', 'userAgent') || '';
    },
    function(t, e, r) {
      var n = r(83),
        i = r(109);
      t.exports = n
        ? {}.toString
        : function() {
            return '[object ' + i(this) + ']';
          };
    },
    function(t, e, r) {
      var n = r(46),
        i = r(17),
        o = r(53),
        a = r(26),
        s = function(t) {
          return function(e, r, s, l) {
            n(r);
            var c = i(e),
              u = o(c),
              h = a(c.length),
              d = t ? h - 1 : 0,
              p = t ? -1 : 1;
            if (s < 2)
              for (;;) {
                if (d in u) {
                  (l = u[d]), (d += p);
                  break;
                }
                if (((d += p), t ? d < 0 : h <= d)) throw TypeError('Reduce of empty array with no initial value');
              }
            for (; t ? d >= 0 : h > d; d += p) d in u && (l = r(l, u[d], d, c));
            return l;
          };
        };
      t.exports = { left: s(!1), right: s(!0) };
    },
    function(t, e, r) {
      var n = r(40),
        i = r(3);
      t.exports = 'process' == n(i.process);
    },
    function(t, e, r) {
      var n = r(45);
      t.exports = n('document', 'documentElement');
    },
    function(t, e, r) {
      var n = r(0),
        i = r(141);
      n({ target: 'Object', stat: !0, forced: Object.assign !== i }, { assign: i });
    },
    function(t, e, r) {
      var n = r(11),
        i = r(1),
        o = r(57),
        a = r(89),
        s = r(70),
        l = r(17),
        c = r(53),
        u = Object.assign,
        h = Object.defineProperty;
      t.exports =
        !u ||
        i(function() {
          if (
            n &&
            1 !==
              u(
                { b: 1 },
                u(
                  h({}, 'a', {
                    enumerable: !0,
                    get: function() {
                      h(this, 'b', { value: 3, enumerable: !1 });
                    },
                  }),
                  { b: 2 }
                )
              ).b
          )
            return !0;
          var t = {},
            e = {},
            r = Symbol();
          return (
            (t[r] = 7),
            'abcdefghijklmnopqrst'.split('').forEach(function(t) {
              e[t] = t;
            }),
            7 != u({}, t)[r] || 'abcdefghijklmnopqrst' != o(u({}, e)).join('')
          );
        })
          ? function(t, e) {
              for (var r = l(t), i = arguments.length, u = 1, h = a.f, d = s.f; i > u; )
                for (var p, f = c(arguments[u++]), y = h ? o(f).concat(h(f)) : o(f), m = y.length, v = 0; m > v; ) (p = y[v++]), (n && !d.call(f, p)) || (r[p] = f[p]);
              return r;
            }
          : u;
    },
    function(t, e, r) {
      var n = r(25),
        i = r(54).f,
        o = {}.toString,
        a = 'object' == typeof window && window && Object.getOwnPropertyNames ? Object.getOwnPropertyNames(window) : [];
      t.exports.f = function(t) {
        return a && '[object Window]' == o.call(t)
          ? (function(t) {
              try {
                return i(t);
              } catch (t) {
                return a.slice();
              }
            })(t)
          : i(n(t));
      };
    },
    function(t, e, r) {
      var n = r(121).IteratorPrototype,
        i = r(47),
        o = r(50),
        a = r(93),
        s = r(61),
        l = function() {
          return this;
        };
      t.exports = function(t, e, r) {
        var c = e + ' Iterator';
        return (t.prototype = i(n, { next: o(1, r) })), a(t, c, !1, !0), (s[c] = l), t;
      };
    },
    function(t, e, r) {
      var n = r(14);
      t.exports = function(t) {
        if (!n(t) && null !== t) throw TypeError("Can't set " + String(t) + ' as a prototype');
        return t;
      };
    },
    function(t, e, r) {
      var n = r(114),
        i = r(17),
        o = r(146),
        a = r(148),
        s = r(26),
        l = r(59),
        c = r(149);
      t.exports = function(t) {
        var e,
          r,
          u,
          h,
          d,
          p,
          f = i(t),
          y = 'function' == typeof this ? this : Array,
          m = arguments.length,
          v = m > 1 ? arguments[1] : void 0,
          b = void 0 !== v,
          g = c(f),
          _ = 0;
        if ((b && (v = n(v, m > 2 ? arguments[2] : void 0, 2)), null == g || (y == Array && a(g)))) for (r = new y((e = s(f.length))); e > _; _++) (p = b ? v(f[_], _) : f[_]), l(r, _, p);
        else for (d = (h = g.call(f)).next, r = new y(); !(u = d.call(h)).done; _++) (p = b ? o(h, v, [u.value, _], !0) : u.value), l(r, _, p);
        return (r.length = _), r;
      };
    },
    function(t, e, r) {
      var n = r(13),
        i = r(147);
      t.exports = function(t, e, r, o) {
        try {
          return o ? e(n(r)[0], r[1]) : e(r);
        } catch (e) {
          throw (i(t), e);
        }
      };
    },
    function(t, e, r) {
      var n = r(13);
      t.exports = function(t) {
        var e = t.return;
        if (void 0 !== e) return n(e.call(t)).value;
      };
    },
    function(t, e, r) {
      var n = r(2),
        i = r(61),
        o = n('iterator'),
        a = Array.prototype;
      t.exports = function(t) {
        return void 0 !== t && (i.Array === t || a[o] === t);
      };
    },
    function(t, e, r) {
      var n = r(109),
        i = r(61),
        o = r(2)('iterator');
      t.exports = function(t) {
        if (null != t) return t[o] || t['@@iterator'] || i[n(t)];
      };
    },
    function(t, e, r) {
      var n = r(2)('iterator'),
        i = !1;
      try {
        var o = 0,
          a = {
            next: function() {
              return { done: !!o++ };
            },
            return: function() {
              i = !0;
            },
          };
        (a[n] = function() {
          return this;
        }),
          Array.from(a, function() {
            throw 2;
          });
      } catch (t) {}
      t.exports = function(t, e) {
        if (!e && !i) return !1;
        var r = !1;
        try {
          var o = {};
          (o[n] = function() {
            return {
              next: function() {
                return { done: (r = !0) };
              },
            };
          }),
            t(o);
        } catch (t) {}
        return r;
      };
    },
    function(t, e, r) {
      var n = r(17),
        i = Math.floor,
        o = ''.replace,
        a = /\$([$&'`]|\d{1,2}|<[^>]*>)/g,
        s = /\$([$&'`]|\d{1,2})/g;
      t.exports = function(t, e, r, l, c, u) {
        var h = r + t.length,
          d = l.length,
          p = s;
        return (
          void 0 !== c && ((c = n(c)), (p = a)),
          o.call(u, p, function(n, o) {
            var a;
            switch (o.charAt(0)) {
              case '$':
                return '$';
              case '&':
                return t;
              case '`':
                return e.slice(0, r);
              case "'":
                return e.slice(h);
              case '<':
                a = c[o.slice(1, -1)];
                break;
              default:
                var s = +o;
                if (0 === s) return n;
                if (s > d) {
                  var u = i(s / 10);
                  return 0 === u ? n : u <= d ? (void 0 === l[u - 1] ? o.charAt(1) : l[u - 1] + o.charAt(1)) : n;
                }
                a = l[s - 1];
            }
            return void 0 === a ? '' : a;
          })
        );
      };
    },
    function(t, e, r) {
      var n = r(45),
        i = r(15),
        o = r(2),
        a = r(11),
        s = o('species');
      t.exports = function(t) {
        var e = n(t),
          r = i.f;
        a &&
          e &&
          !e[s] &&
          r(e, s, {
            configurable: !0,
            get: function() {
              return this;
            },
          });
      };
    },
    function(t, e, r) {
      var n = r(0),
        i = r(44).every;
      n(
        { target: 'Array', proto: !0, forced: !r(43)('every') },
        {
          every: function(t) {
            return i(this, t, arguments.length > 1 ? arguments[1] : void 0);
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(3),
        i = r(101).trim,
        o = r(102),
        a = n.parseInt,
        s = /^[+-]?0[Xx]/,
        l = 8 !== a(o + '08') || 22 !== a(o + '0x16');
      t.exports = l
        ? function(t, e) {
            var r = i(String(t));
            return a(r, e >>> 0 || (s.test(r) ? 16 : 10));
          }
        : a;
    },
    function(t, e, r) {
      var n = r(13),
        i = r(46),
        o = r(2)('species');
      t.exports = function(t, e) {
        var r,
          a = n(t).constructor;
        return void 0 === a || null == (r = n(a)[o]) ? e : i(r);
      };
    },
    function(t, e, r) {
      var n = r(3),
        i = r(101).trim,
        o = r(102),
        a = n.parseFloat,
        s = 1 / a(o + '-0') != -1 / 0;
      t.exports = s
        ? function(t) {
            var e = i(String(t)),
              r = a(e);
            return 0 === r && '-' == e.charAt(0) ? -0 : r;
          }
        : a;
    },
    function(t, e, r) {
      var n = r(0),
        i = r(46),
        o = r(17),
        a = r(1),
        s = r(43),
        l = [],
        c = l.sort,
        u = a(function() {
          l.sort(void 0);
        }),
        h = a(function() {
          l.sort(null);
        }),
        d = s('sort');
      n(
        { target: 'Array', proto: !0, forced: u || !h || !d },
        {
          sort: function(t) {
            return void 0 === t ? c.call(o(this)) : c.call(o(this), i(t));
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(0),
        i = r(87),
        o = r(55),
        a = r(26),
        s = r(17),
        l = r(91),
        c = r(59),
        u = r(60)('splice'),
        h = Math.max,
        d = Math.min;
      n(
        { target: 'Array', proto: !0, forced: !u },
        {
          splice: function(t, e) {
            var r,
              n,
              u,
              p,
              f,
              y,
              m = s(this),
              v = a(m.length),
              b = i(t, v),
              g = arguments.length;
            if ((0 === g ? (r = n = 0) : 1 === g ? ((r = 0), (n = v - b)) : ((r = g - 2), (n = d(h(o(e), 0), v - b))), v + r - n > 9007199254740991))
              throw TypeError('Maximum allowed length exceeded');
            for (u = l(m, n), p = 0; p < n; p++) (f = b + p) in m && c(u, p, m[f]);
            if (((u.length = n), r < n)) {
              for (p = b; p < v - n; p++) (y = p + r), (f = p + n) in m ? (m[y] = m[f]) : delete m[y];
              for (p = v; p > v - n + r; p--) delete m[p - 1];
            } else if (r > n) for (p = v - n; p > b; p--) (y = p + r - 1), (f = p + n - 1) in m ? (m[y] = m[f]) : delete m[y];
            for (p = 0; p < r; p++) m[p + b] = arguments[p + 2];
            return (m.length = v - n + r), u;
          },
        }
      );
    },
    function(t, e, r) {
      var n = r(11),
        i = r(3),
        o = r(90),
        a = r(31),
        s = r(16),
        l = r(40),
        c = r(124),
        u = r(49),
        h = r(1),
        d = r(47),
        p = r(54).f,
        f = r(36).f,
        y = r(15).f,
        m = r(101).trim,
        v = i.Number,
        b = v.prototype,
        g = 'Number' == l(d(b)),
        _ = function(t) {
          var e,
            r,
            n,
            i,
            o,
            a,
            s,
            l,
            c = u(t, !1);
          if ('string' == typeof c && c.length > 2)
            if (43 === (e = (c = m(c)).charCodeAt(0)) || 45 === e) {
              if (88 === (r = c.charCodeAt(2)) || 120 === r) return NaN;
            } else if (48 === e) {
              switch (c.charCodeAt(1)) {
                case 66:
                case 98:
                  (n = 2), (i = 49);
                  break;
                case 79:
                case 111:
                  (n = 8), (i = 55);
                  break;
                default:
                  return +c;
              }
              for (a = (o = c.slice(2)).length, s = 0; s < a; s++) if ((l = o.charCodeAt(s)) < 48 || l > i) return NaN;
              return parseInt(o, n);
            }
          return +c;
        };
      if (o('Number', !v(' 0o1') || !v('0b1') || v('+0x1'))) {
        for (
          var w,
            k = function(t) {
              var e = arguments.length < 1 ? 0 : t,
                r = this;
              return r instanceof k &&
                (g
                  ? h(function() {
                      b.valueOf.call(r);
                    })
                  : 'Number' != l(r))
                ? c(new v(_(e)), r, k)
                : _(e);
            },
            x = n
              ? p(v)
              : 'MAX_VALUE,MIN_VALUE,NaN,NEGATIVE_INFINITY,POSITIVE_INFINITY,EPSILON,isFinite,isInteger,isNaN,isSafeInteger,MAX_SAFE_INTEGER,MIN_SAFE_INTEGER,parseFloat,parseInt,isInteger,fromString,range'.split(
                  ','
                ),
            j = 0;
          x.length > j;
          j++
        )
          s(v, (w = x[j])) && !s(k, w) && y(k, w, f(v, w));
        (k.prototype = b), (b.constructor = k), a(i, 'Number', k);
      }
    },
    function(t, e, r) {
      r.r(e),
        r.d(e, 'JSONEditor', function() {
          return ir;
        });
      r(79), r(5), r(41), r(42), r(56), r(71), r(18), r(19), r(33), r(34), r(140), r(12), r(20), r(6), r(7), r(8), r(4), r(9), r(10), r(37), r(35), r(38), r(62), r(27), r(74), r(75), r(39);
      var n = [
          'actionscript',
          'batchfile',
          'c',
          'c++',
          'cpp',
          'coffee',
          'csharp',
          'css',
          'dart',
          'django',
          'ejs',
          'erlang',
          'golang',
          'groovy',
          'handlebars',
          'haskell',
          'haxe',
          'html',
          'ini',
          'jade',
          'java',
          'javascript',
          'json',
          'less',
          'lisp',
          'lua',
          'makefile',
          'matlab',
          'mysql',
          'objectivec',
          'pascal',
          'perl',
          'pgsql',
          'php',
          'python',
          'r',
          'ruby',
          'sass',
          'scala',
          'scss',
          'smarty',
          'sql',
          'sqlserver',
          'stylus',
          'svg',
          'twig',
          'vbscript',
          'xml',
          'yaml',
        ],
        i = [
          function(t) {
            return 'string' === t.type && 'color' === t.format && 'colorpicker';
          },
          function(t) {
            return 'string' === t.type && ['ip', 'ipv4', 'ipv6', 'hostname'].includes(t.format) && 'ip';
          },
          function(t) {
            return 'string' === t.type && n.includes(t.format) && 'ace';
          },
          function(t) {
            return 'string' === t.type && ['xhtml', 'bbcode'].includes(t.format) && 'sceditor';
          },
          function(t) {
            return 'string' === t.type && 'markdown' === t.format && 'simplemde';
          },
          function(t) {
            return 'string' === t.type && 'jodit' === t.format && 'jodit';
          },
          function(t) {
            return 'string' === t.type && 'autocomplete' === t.format && 'autocomplete';
          },
          function(t) {
            return 'string' === t.type && 'uuid' === t.format && 'uuid';
          },
          function(t) {
            return 'info' === t.format && 'info';
          },
          function(t) {
            return 'button' === t.format && 'button';
          },
          function(t) {
            if (('integer' === t.type || 'number' === t.type) && 'stepper' === t.format) return 'stepper';
          },
          function(t) {
            if (t.links) for (var e = 0; e < t.links.length; e++) if (t.links[e].rel && 'describedby' === t.links[e].rel.toLowerCase()) return 'describedBy';
          },
          function(t) {
            return ['string', 'integer'].includes(t.type) && ['starrating', 'rating'].includes(t.format) && 'starrating';
          },
          function(t) {
            return ['string', 'integer'].includes(t.type) && ['date', 'time', 'datetime-local'].includes(t.format) && 'datetime';
          },
          function(t) {
            return (t.oneOf || t.anyOf) && 'multiple';
          },
          function(t) {
            if ('array' === t.type && t.items && !Array.isArray(t.items) && ['string', 'number', 'integer'].includes(t.items.type)) {
              if ('choices' === t.format) return 'arrayChoices';
              if (t.uniqueItems) {
                if ('selectize' === t.format) return 'arraySelectize';
                if ('select2' === t.format) return 'arraySelect2';
                if (t.items.enum) return 'multiselect';
              }
            }
          },
          function(t) {
            if (t.enum) {
              if ('array' === t.type || 'object' === t.type) return 'enum';
              if ('number' === t.type || 'integer' === t.type || 'string' === t.type)
                return 'radio' === t.format ? 'radio' : 'select2' === t.format ? 'select2' : 'selectize' === t.format ? 'selectize' : 'choices' === t.format ? 'choices' : 'select';
            }
          },
          function(t) {
            if (t.enumSource) return 'radio' === t.format ? 'radio' : 'select2' === t.format ? 'select2' : 'selectize' === t.format ? 'selectize' : 'choices' === t.format ? 'choices' : 'select';
          },
          function(t) {
            return 'array' === t.type && 'table' === t.format && 'table';
          },
          function(t) {
            return 'string' === t.type && 'url' === t.format && window.FileReader && t.options && t.options.upload === Object(t.options.upload) && 'upload';
          },
          function(t) {
            return 'string' === t.type && t.media && 'base64' === t.media.binaryEncoding && 'base64';
          },
          function(t) {
            return 'any' === t.type && 'multiple';
          },
          function(t) {
            if ('boolean' === t.type)
              return 'checkbox' === t.format || (t.options && t.options.checkbox)
                ? 'checkbox'
                : 'select2' === t.format
                ? 'select2'
                : 'selectize' === t.format
                ? 'selectize'
                : 'choices' === t.format
                ? 'choices'
                : 'select';
          },
          function(t) {
            return 'string' === t.type && 'signature' === t.format && 'signature';
          },
          function(t) {
            return 'string' == typeof t.type && t.type;
          },
          function(t) {
            return !t.type && t.properties && 'object';
          },
          function(t) {
            return 'string' != typeof t.type && 'multiple';
          },
        ];
      function o(t, e) {
        return (
          (function(t) {
            if (Array.isArray(t)) return t;
          })(t) ||
          (function(t, e) {
            var r = t && (('undefined' != typeof Symbol && t[Symbol.iterator]) || t['@@iterator']);
            if (null == r) return;
            var n,
              i,
              o = [],
              a = !0,
              s = !1;
            try {
              for (r = r.call(t); !(a = (n = r.next()).done) && (o.push(n.value), !e || o.length !== e); a = !0);
            } catch (t) {
              (s = !0), (i = t);
            } finally {
              try {
                a || null == r.return || r.return();
              } finally {
                if (s) throw i;
              }
            }
            return o;
          })(t, e) ||
          (function(t, e) {
            if (!t) return;
            if ('string' == typeof t) return a(t, e);
            var r = Object.prototype.toString.call(t).slice(8, -1);
            'Object' === r && t.constructor && (r = t.constructor.name);
            if ('Map' === r || 'Set' === r) return Array.from(t);
            if ('Arguments' === r || /^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(r)) return a(t, e);
          })(t, e) ||
          (function() {
            throw new TypeError('Invalid attempt to destructure non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.');
          })()
        );
      }
      function a(t, e) {
        (null == e || e > t.length) && (e = t.length);
        for (var r = 0, n = new Array(e); r < e; r++) n[r] = t[r];
        return n;
      }
      var s = {},
        l = {};
      (l.en = {
        error_notset: 'Property must be set',
        error_notempty: 'Value required',
        error_enum: 'Value must be one of the enumerated values',
        error_const: 'Value must be the constant value',
        error_anyOf: 'Value must validate against at least one of the provided schemas',
        error_oneOf: 'Value must validate against exactly one of the provided schemas. It currently validates against {{0}} of the schemas.',
        error_not: 'Value must not validate against the provided schema',
        error_type_union: 'Value must be one of the provided types',
        error_type: 'Value must be of type {{0}}',
        error_disallow_union: 'Value must not be one of the provided disallowed types',
        error_disallow: 'Value must not be of type {{0}}',
        error_multipleOf: 'Value must be a multiple of {{0}}',
        error_maximum_excl: 'Value must be less than {{0}}',
        error_maximum_incl: 'Value must be at most {{0}}',
        error_minimum_excl: 'Value must be greater than {{0}}',
        error_minimum_incl: 'Value must be at least {{0}}',
        error_maxLength: 'Value must be at most {{0}} characters long',
        error_minLength: 'Value must be at least {{0}} characters long',
        error_pattern: 'Value must match the pattern {{0}}',
        error_additionalItems: 'No additional items allowed in this array',
        error_maxItems: 'Value must have at most {{0}} items',
        error_minItems: 'Value must have at least {{0}} items',
        error_uniqueItems: 'Array must have unique items',
        error_maxProperties: 'Object must have at most {{0}} properties',
        error_minProperties: 'Object must have at least {{0}} properties',
        error_required: "Object is missing the required property '{{0}}'",
        error_additional_properties: 'No additional properties allowed, but property {{0}} is set',
        error_property_names_exceeds_maxlength: 'Property name {{0}} exceeds maxLength',
        error_property_names_enum_mismatch: 'Property name {{0}} does not match any enum values',
        error_property_names_const_mismatch: 'Property name {{0}} does not match the const value',
        error_property_names_pattern_mismatch: 'Property name {{0}} does not match pattern',
        error_property_names_false: 'Property name {{0}} fails when propertyName is false',
        error_property_names_maxlength: 'Property name {{0}} cannot match invalid maxLength',
        error_property_names_enum: 'Property name {{0}} cannot match invalid enum',
        error_property_names_pattern: 'Property name {{0}} cannot match invalid pattern',
        error_property_names_unsupported: 'Unsupported propertyName {{0}}',
        error_dependency: 'Must have property {{0}}',
        error_date: 'Date must be in the format {{0}}',
        error_time: 'Time must be in the format {{0}}',
        error_datetime_local: 'Datetime must be in the format {{0}}',
        error_invalid_epoch: 'Date must be greater than 1 January 1970',
        error_ipv4: 'Value must be a valid IPv4 address in the form of 4 numbers between 0 and 255, separated by dots',
        error_ipv6: 'Value must be a valid IPv6 address',
        error_hostname: 'The hostname has the wrong format',
        button_save: 'Save',
        button_copy: 'Copy',
        button_cancel: 'Cancel',
        button_add: 'Add',
        button_delete_all: 'All',
        button_delete_all_title: 'Delete All',
        button_delete_last: 'Last {{0}}',
        button_delete_last_title: 'Delete Last {{0}}',
        button_add_row_title: 'Add {{0}}',
        button_move_down_title: 'Move down',
        button_move_up_title: 'Move up',
        button_properties: 'Properties',
        button_object_properties: 'Object Properties',
        button_copy_row_title: 'Copy {{0}}',
        button_delete_row_title: 'Delete {{0}}',
        button_delete_row_title_short: 'Delete',
        button_copy_row_title_short: 'Copy',
        button_collapse: 'Collapse',
        button_expand: 'Expand',
        button_edit_json: 'Edit JSON',
        button_upload: 'Upload',
        flatpickr_toggle_button: 'Toggle',
        flatpickr_clear_button: 'Clear',
        choices_placeholder_text: 'Start typing to add value',
        default_array_item_title: 'item',
        button_delete_node_warning: 'Are you sure you want to remove this node?',
      }),
        Object.entries(s).forEach(function(t) {
          var e = o(t, 2),
            r = e[0],
            n = e[1];
          s[r].options = n.options || {};
        });
      var c = {
        options: {
          upload: function(t, e, r) {
            console.log('Upload handler required for upload editor');
          },
          prompt_before_delete: !0,
          use_default_values: !0,
          max_depth: 0,
        },
        theme: 'html',
        template: 'default',
        themes: {},
        callbacks: {},
        templates: {},
        iconlibs: {},
        editors: s,
        languages: l,
        resolvers: i,
        custom_validators: [],
        default_language: 'en',
        language: 'en',
        translate: function(t, e) {
          var r = c.languages[c.language];
          if (!r) throw new Error('Unknown language '.concat(c.language));
          var n = r[t] || c.languages.en[t] || t;
          if (e) for (var i = 0; i < e.length; i++) n = n.replace(new RegExp('\\{\\{'.concat(i, '}}'), 'g'), e[i]);
          return n;
        },
        translateProperty: function(t, e) {
          return t;
        },
      };
      r(76), r(153), r(63), r(100), r(77), r(64), r(78), r(28), r(125), r(126), r(65);
      function u(t, e, r, n) {
        try {
          switch (t.format) {
            case 'ipv4':
              !(function(t) {
                var e = t.split('.');
                if (4 !== e.length) throw new Error('error_ipv4');
                e.forEach(function(t) {
                  if (isNaN(+t) || +t < 0 || +t > 255) throw new Error('error_ipv4');
                });
              })(e);
              break;
            case 'ipv6':
              !(function(t) {
                if (
                  !t.match(
                    '^(?:(?:(?:[a-fA-F0-9]{1,4}:){6}|(?=(?:[a-fA-F0-9]{0,4}:){2,6}(?:[0-9]{1,3}.){3}[0-9]{1,3}$)(([0-9a-fA-F]{1,4}:){1,5}|:)((:[0-9a-fA-F]{1,4}){1,5}:|:)|::(?:[a-fA-F0-9]{1,4}:){5})(?:(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9]).){3}(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])|(?:[a-fA-F0-9]{1,4}:){7}[a-fA-F0-9]{1,4}|(?=(?:[a-fA-F0-9]{0,4}:){0,7}[a-fA-F0-9]{0,4}$)(([0-9a-fA-F]{1,4}:){1,7}|:)((:[0-9a-fA-F]{1,4}){1,7}|:)|(?:[a-fA-F0-9]{1,4}:){7}:|:(:[a-fA-F0-9]{1,4}){7})$'
                  )
                )
                  throw new Error('error_ipv6');
              })(e);
              break;
            case 'hostname':
              !(function(t) {
                if (!t.match('(?=^.{4,253}$)(^((?!-)[a-zA-Z0-9-]{0,62}[a-zA-Z0-9].)+[a-zA-Z]{2,63}$)')) throw new Error('error_hostname');
              })(e);
          }
          return [];
        } catch (t) {
          return [{ path: r, property: 'format', message: n(t.message) }];
        }
      }
      r(127);
      function h(t) {
        return (h =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function d(t) {
        return null !== t && 'object' === h(t) && !t.nodeType && t !== t.window && !(t.constructor && !v(t.constructor.prototype, 'isPrototypeOf'));
      }
      function p(t) {
        return d(t) ? f({}, t) : Array.isArray(t) ? t.map(p) : t;
      }
      function f(t) {
        for (var e = arguments.length, r = new Array(e > 1 ? e - 1 : 0), n = 1; n < e; n++) r[n - 1] = arguments[n];
        return (
          r.forEach(function(e) {
            e &&
              Object.keys(e).forEach(function(r) {
                e[r] && d(e[r]) ? (v(t, r) || (t[r] = {}), f(t[r], e[r])) : Array.isArray(e[r]) ? (t[r] = p(e[r])) : (t[r] = e[r]);
              });
          }),
          t
        );
      }
      function y(t, e) {
        var r = document.createEvent('HTMLEvents');
        r.initEvent(e, !0, !0), t.dispatchEvent(r);
      }
      function m(t) {
        return t && ('[object ShadowRoot]' === t.toString() ? t : m(t.parentNode));
      }
      function v(t, e) {
        return t && Object.prototype.hasOwnProperty.call(t, e);
      }
      var b = /^\s*(-|\+)?(\d+|(\d*(\.\d*)))([eE][+-]?\d+)?\s*$/;
      var g = /^\s*(-|\+)?(\d+)\s*$/;
      function _(t, e) {
        var r = ('undefined' != typeof Symbol && t[Symbol.iterator]) || t['@@iterator'];
        if (!r) {
          if (Array.isArray(t) || (r = E(t)) || (e && t && 'number' == typeof t.length)) {
            r && (t = r);
            var n = 0,
              i = function() {};
            return {
              s: i,
              n: function() {
                return n >= t.length ? { done: !0 } : { done: !1, value: t[n++] };
              },
              e: function(t) {
                throw t;
              },
              f: i,
            };
          }
          throw new TypeError('Invalid attempt to iterate non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.');
        }
        var o,
          a = !0,
          s = !1;
        return {
          s: function() {
            r = r.call(t);
          },
          n: function() {
            var t = r.next();
            return (a = t.done), t;
          },
          e: function(t) {
            (s = !0), (o = t);
          },
          f: function() {
            try {
              a || null == r.return || r.return();
            } finally {
              if (s) throw o;
            }
          },
        };
      }
      function w(t, e) {
        var r = Object.keys(t);
        if (Object.getOwnPropertySymbols) {
          var n = Object.getOwnPropertySymbols(t);
          e &&
            (n = n.filter(function(e) {
              return Object.getOwnPropertyDescriptor(t, e).enumerable;
            })),
            r.push.apply(r, n);
        }
        return r;
      }
      function k(t) {
        for (var e = 1; e < arguments.length; e++) {
          var r = null != arguments[e] ? arguments[e] : {};
          e % 2
            ? w(Object(r), !0).forEach(function(e) {
                x(t, e, r[e]);
              })
            : Object.getOwnPropertyDescriptors
            ? Object.defineProperties(t, Object.getOwnPropertyDescriptors(r))
            : w(Object(r)).forEach(function(e) {
                Object.defineProperty(t, e, Object.getOwnPropertyDescriptor(r, e));
              });
        }
        return t;
      }
      function x(t, e, r) {
        return e in t ? Object.defineProperty(t, e, { value: r, enumerable: !0, configurable: !0, writable: !0 }) : (t[e] = r), t;
      }
      function j(t, e) {
        return (
          (function(t) {
            if (Array.isArray(t)) return t;
          })(t) ||
          (function(t, e) {
            var r = t && (('undefined' != typeof Symbol && t[Symbol.iterator]) || t['@@iterator']);
            if (null == r) return;
            var n,
              i,
              o = [],
              a = !0,
              s = !1;
            try {
              for (r = r.call(t); !(a = (n = r.next()).done) && (o.push(n.value), !e || o.length !== e); a = !0);
            } catch (t) {
              (s = !0), (i = t);
            } finally {
              try {
                a || null == r.return || r.return();
              } finally {
                if (s) throw i;
              }
            }
            return o;
          })(t, e) ||
          E(t, e) ||
          (function() {
            throw new TypeError('Invalid attempt to destructure non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.');
          })()
        );
      }
      function O(t) {
        return (
          (function(t) {
            if (Array.isArray(t)) return C(t);
          })(t) ||
          (function(t) {
            if (('undefined' != typeof Symbol && null != t[Symbol.iterator]) || null != t['@@iterator']) return Array.from(t);
          })(t) ||
          E(t) ||
          (function() {
            throw new TypeError('Invalid attempt to spread non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.');
          })()
        );
      }
      function E(t, e) {
        if (t) {
          if ('string' == typeof t) return C(t, e);
          var r = Object.prototype.toString.call(t).slice(8, -1);
          return (
            'Object' === r && t.constructor && (r = t.constructor.name),
            'Map' === r || 'Set' === r ? Array.from(t) : 'Arguments' === r || /^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(r) ? C(t, e) : void 0
          );
        }
      }
      function C(t, e) {
        (null == e || e > t.length) && (e = t.length);
        for (var r = 0, n = new Array(e); r < e; r++) n[r] = t[r];
        return n;
      }
      function S(t) {
        return (S =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function A(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      var P = (function() {
        function t(e, r, n, i) {
          !(function(t, e) {
            if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
          })(this, t),
            (this.jsoneditor = e),
            (this.schema = r || this.jsoneditor.schema),
            (this.options = n || {}),
            (this.translate = this.jsoneditor.translate || i.translate),
            (this.translateProperty = this.jsoneditor.translateProperty || i.translateProperty),
            (this.defaults = i),
            (this._validateSubSchema = {
              const: function(t, e, r) {
                return JSON.stringify(t.const) === JSON.stringify(e) && !(Array.isArray(e) || 'object' === S(e)) ? [] : [{ path: r, property: 'const', message: this.translate('error_const') }];
              },
              enum: function(t, e, r) {
                var n = JSON.stringify(e);
                return t.enum.some(function(t) {
                  return n === JSON.stringify(t);
                })
                  ? []
                  : [{ path: r, property: 'enum', message: this.translate('error_enum') }];
              },
              extends: function(t, e, r) {
                var n = this;
                return t.extends.reduce(function(t, i) {
                  return t.push.apply(t, O(n._validateSchema(i, e, r))), t;
                }, []);
              },
              allOf: function(t, e, r) {
                var n = this;
                return t.allOf.reduce(function(t, i) {
                  return t.push.apply(t, O(n._validateSchema(i, e, r))), t;
                }, []);
              },
              anyOf: function(t, e, r) {
                var n = this;
                return t.anyOf.some(function(t) {
                  return !n._validateSchema(t, e, r).length;
                })
                  ? []
                  : [{ path: r, property: 'anyOf', message: this.translate('error_anyOf') }];
              },
              oneOf: function(t, e, r) {
                var n = this,
                  i = 0,
                  o = [];
                t.oneOf.forEach(function(t, a) {
                  var s = n._validateSchema(t, e, r);
                  s.length || i++,
                    s.forEach(function(t) {
                      t.path = ''
                        .concat(r, '.oneOf[')
                        .concat(a, ']')
                        .concat(t.path.substr(r.length));
                    }),
                    o.push.apply(o, O(s));
                });
                var a = [];
                return 1 !== i && (a.push({ path: r, property: 'oneOf', message: this.translate('error_oneOf', [i]) }), a.push.apply(a, o)), a;
              },
              not: function(t, e, r) {
                return this._validateSchema(t.not, e, r).length ? [] : [{ path: r, property: 'not', message: this.translate('error_not') }];
              },
              type: function(t, e, r) {
                var n = this;
                if (Array.isArray(t.type)) {
                  if (
                    !t.type.some(function(t) {
                      return n._checkType(t, e);
                    })
                  )
                    return [{ path: r, property: 'type', message: this.translate('error_type_union') }];
                } else if (['date', 'time', 'datetime-local'].includes(t.format) && 'integer' === t.type) {
                  if (!this._checkType('string', ''.concat(e))) return [{ path: r, property: 'type', message: this.translate('error_type', [t.format]) }];
                } else if (!this._checkType(t.type, e)) return [{ path: r, property: 'type', message: this.translate('error_type', [t.type]) }];
                return [];
              },
              disallow: function(t, e, r) {
                var n = this;
                if (Array.isArray(t.disallow)) {
                  if (
                    t.disallow.some(function(t) {
                      return n._checkType(t, e);
                    })
                  )
                    return [{ path: r, property: 'disallow', message: this.translate('error_disallow_union') }];
                } else if (this._checkType(t.disallow, e)) return [{ path: r, property: 'disallow', message: this.translate('error_disallow', [t.disallow]) }];
                return [];
              },
            }),
            (this._validateNumberSubSchema = {
              multipleOf: function(t, e, r) {
                return this._validateNumberSubSchemaMultipleDivisible(t, e, r);
              },
              divisibleBy: function(t, e, r) {
                return this._validateNumberSubSchemaMultipleDivisible(t, e, r);
              },
              maximum: function(t, e, r) {
                var n = t.exclusiveMaximum ? e < t.maximum : e <= t.maximum;
                return (
                  window.math
                    ? (n = window.math[t.exclusiveMaximum ? 'smaller' : 'smallerEq'](window.math.bignumber(e), window.math.bignumber(t.maximum)))
                    : window.Decimal && (n = new window.Decimal(e)[t.exclusiveMaximum ? 'lt' : 'lte'](new window.Decimal(t.maximum))),
                  n ? [] : [{ path: r, property: 'maximum', message: this.translate(t.exclusiveMaximum ? 'error_maximum_excl' : 'error_maximum_incl', [t.maximum]) }]
                );
              },
              minimum: function(t, e, r) {
                var n = t.exclusiveMinimum ? e > t.minimum : e >= t.minimum;
                return (
                  window.math
                    ? (n = window.math[t.exclusiveMinimum ? 'larger' : 'largerEq'](window.math.bignumber(e), window.math.bignumber(t.minimum)))
                    : window.Decimal && (n = new window.Decimal(e)[t.exclusiveMinimum ? 'gt' : 'gte'](new window.Decimal(t.minimum))),
                  n ? [] : [{ path: r, property: 'minimum', message: this.translate(t.exclusiveMinimum ? 'error_minimum_excl' : 'error_minimum_incl', [t.minimum]) }]
                );
              },
            }),
            (this._validateStringSubSchema = {
              maxLength: function(t, e, r) {
                var n = [];
                return ''.concat(e).length > t.maxLength && n.push({ path: r, property: 'maxLength', message: this.translate('error_maxLength', [t.maxLength]) }), n;
              },
              minLength: function(t, e, r) {
                return ''.concat(e).length < t.minLength ? [{ path: r, property: 'minLength', message: this.translate(1 === t.minLength ? 'error_notempty' : 'error_minLength', [t.minLength]) }] : [];
              },
              pattern: function(t, e, r) {
                return new RegExp(t.pattern).test(e)
                  ? []
                  : [{ path: r, property: 'pattern', message: t.options && t.options.patternmessage ? t.options.patternmessage : this.translate('error_pattern', [t.pattern]) }];
              },
            }),
            (this._validateArraySubSchema = {
              items: function(t, e, r) {
                var n = this,
                  i = [];
                if (Array.isArray(t.items))
                  for (var o = 0; o < e.length; o++)
                    if (t.items[o]) i.push.apply(i, O(this._validateSchema(t.items[o], e[o], ''.concat(r, '.').concat(o))));
                    else {
                      if (!0 === t.additionalItems) break;
                      if (!t.additionalItems) {
                        if (!1 === t.additionalItems) {
                          i.push({ path: r, property: 'additionalItems', message: this.translate('error_additionalItems') });
                          break;
                        }
                        break;
                      }
                      i.push.apply(i, O(this._validateSchema(t.additionalItems, e[o], ''.concat(r, '.').concat(o))));
                    }
                else
                  e.forEach(function(e, o) {
                    i.push.apply(i, O(n._validateSchema(t.items, e, ''.concat(r, '.').concat(o))));
                  });
                return i;
              },
              maxItems: function(t, e, r) {
                return e.length > t.maxItems ? [{ path: r, property: 'maxItems', message: this.translate('error_maxItems', [t.maxItems]) }] : [];
              },
              minItems: function(t, e, r) {
                return e.length < t.minItems ? [{ path: r, property: 'minItems', message: this.translate('error_minItems', [t.minItems]) }] : [];
              },
              uniqueItems: function(t, e, r) {
                for (var n = {}, i = 0; i < e.length; i++) {
                  var o = JSON.stringify(e[i]);
                  if (n[o]) return [{ path: r, property: 'uniqueItems', message: this.translate('error_uniqueItems') }];
                  n[o] = !0;
                }
                return [];
              },
            }),
            (this._validateObjectSubSchema = {
              maxProperties: function(t, e, r) {
                return Object.keys(e).length > t.maxProperties ? [{ path: r, property: 'maxProperties', message: this.translate('error_maxProperties', [t.maxProperties]) }] : [];
              },
              minProperties: function(t, e, r) {
                return Object.keys(e).length < t.minProperties ? [{ path: r, property: 'minProperties', message: this.translate('error_minProperties', [t.minProperties]) }] : [];
              },
              required: function(t, e, r) {
                var n = this,
                  i = [];
                return (
                  Array.isArray(t.required) &&
                    t.required.forEach(function(o) {
                      if (void 0 === e[o]) {
                        var a = n.jsoneditor.getEditor(''.concat(r, '.').concat(o));
                        (a && !1 === a.dependenciesFulfilled) ||
                          (a && ['button', 'info'].includes(a.schema.format || a.schema.type)) ||
                          i.push({
                            path: r,
                            property: 'required',
                            message: n.translate('error_required', [t && t.properties && t.properties[o] && t.properties[o].title ? t.properties[o].title : o]),
                          });
                      }
                    }),
                  i
                );
              },
              properties: function(t, e, r, n) {
                var i = this,
                  o = [];
                return (
                  Object.entries(t.properties).forEach(function(t) {
                    var a = j(t, 2),
                      s = a[0],
                      l = a[1];
                    (n[s] = !0), o.push.apply(o, O(i._validateSchema(l, e[s], ''.concat(r, '.').concat(s))));
                  }),
                  o
                );
              },
              patternProperties: function(t, e, r, n) {
                var i = this,
                  o = [];
                return (
                  Object.entries(t.patternProperties).forEach(function(t) {
                    var a = j(t, 2),
                      s = a[0],
                      l = a[1],
                      c = new RegExp(s);
                    Object.entries(e).forEach(function(t) {
                      var e = j(t, 2),
                        a = e[0],
                        s = e[1];
                      c.test(a) && ((n[a] = !0), o.push.apply(o, O(i._validateSchema(l, s, ''.concat(r, '.').concat(a)))));
                    });
                  }),
                  o
                );
              },
            }),
            (this._validateObjectSubSchema2 = {
              propertyNames: function(t, e, r, n) {
                for (
                  var i = this,
                    o = [],
                    a = Object.keys(e),
                    s = null,
                    l = function(e) {
                      var n = '';
                      return (
                        (s = a[e]),
                        'boolean' == typeof t.propertyNames
                          ? !0 === t.propertyNames
                            ? 'continue'
                            : (o.push({ path: r, property: 'propertyNames', message: i.translate('error_property_names_false', [s]) }), 'break')
                          : Object.entries(t.propertyNames).every(function(t) {
                              var e = j(t, 2),
                                a = e[0],
                                l = e[1],
                                c = !1;
                              switch (a) {
                                case 'maxLength':
                                  if ('number' != typeof l) {
                                    n = 'error_property_names_maxlength';
                                    break;
                                  }
                                  if (s.length > l) {
                                    n = 'error_property_names_exceeds_maxlength';
                                    break;
                                  }
                                  return !0;
                                case 'const':
                                  if (l !== s) {
                                    n = 'error_property_names_const_mismatch';
                                    break;
                                  }
                                  return !0;
                                case 'enum':
                                  if (!Array.isArray(l)) {
                                    n = 'error_property_names_enum';
                                    break;
                                  }
                                  if (
                                    (l.forEach(function(t) {
                                      t === s && (c = !0);
                                    }),
                                    !c)
                                  ) {
                                    n = 'error_property_names_enum_mismatch';
                                    break;
                                  }
                                  return !0;
                                case 'pattern':
                                  if ('string' != typeof l) {
                                    n = 'error_property_names_pattern';
                                    break;
                                  }
                                  if (!new RegExp(l).test(s)) {
                                    n = 'error_property_names_pattern_mismatch';
                                    break;
                                  }
                                  return !0;
                                default:
                                  return o.push({ path: r, property: 'propertyNames', message: i.translate('error_property_names_unsupported', [a]) }), !1;
                              }
                              return o.push({ path: r, property: 'propertyNames', message: i.translate(n, [s]) }), !1;
                            })
                          ? void 0
                          : 'break'
                      );
                    },
                    c = 0;
                  c < a.length;
                  c++
                ) {
                  var u = l(c);
                  if ('continue' !== u && 'break' === u) break;
                }
                return o;
              },
              additionalProperties: function(t, e, r, n) {
                for (var i = [], o = Object.keys(e), a = 0; a < o.length; a++) {
                  var s = o[a];
                  if (!n[s]) {
                    if (!t.additionalProperties) {
                      i.push({ path: r, property: 'additionalProperties', message: this.translate('error_additional_properties', [s]) });
                      break;
                    }
                    if (!0 === t.additionalProperties) break;
                    i.push.apply(i, O(this._validateSchema(t.additionalProperties, e[s], ''.concat(r, '.').concat(s))));
                  }
                }
                return i;
              },
              dependencies: function(t, e, r) {
                var n = this,
                  i = [];
                return (
                  Object.entries(t.dependencies).forEach(function(t) {
                    var o = j(t, 2),
                      a = o[0],
                      s = o[1];
                    void 0 !== e[a] &&
                      (Array.isArray(s)
                        ? s.forEach(function(t) {
                            void 0 === e[t] && i.push({ path: r, property: 'dependencies', message: n.translate('error_dependency', [t]) });
                          })
                        : i.push.apply(i, O(n._validateSchema(s, e, r))));
                  }),
                  i
                );
              },
            });
        }
        var e, r, n;
        return (
          (e = t),
          (r = [
            {
              key: 'fitTest',
              value: function(t, e) {
                var r = arguments.length > 2 && void 0 !== arguments[2] ? arguments[2] : 1e7,
                  n = { match: 0, extra: 0 };
                if ('object' === S(t) && null !== t) {
                  var i = this._getSchema(e);
                  if (i.anyOf) {
                    var o,
                      a = k({}, n),
                      s = _(i.anyOf);
                    try {
                      for (s.s(); !(o = s.n()).done; ) {
                        var l = o.value,
                          c = this.fitTest(t, l, r);
                        (c.match > a.match || (c.match === a.match && c.extra < a.extra)) && (a = c);
                      }
                    } catch (t) {
                      s.e(t);
                    } finally {
                      s.f();
                    }
                    return a;
                  }
                  var u = this._getSchema(e).properties;
                  for (var h in u)
                    if (v(u, h)) {
                      if ('object' === S(t[h]) && 'object' === S(u[h]) && 'object' === S(u[h].properties)) {
                        var d = this.fitTest(t[h], u[h], r / 100);
                        (n.match += d.match), (n.extra += d.extra);
                      }
                      void 0 !== t[h] && (n.match += r);
                    } else n.extra += r;
                }
                return n;
              },
            },
            {
              key: '_getSchema',
              value: function(t) {
                return void 0 === t ? f({}, this.jsoneditor.expandRefs(this.schema)) : t;
              },
            },
            {
              key: 'validate',
              value: function(t) {
                return this._validateSchema(this.schema, t);
              },
            },
            {
              key: '_validateSchema',
              value: function(t, e, r) {
                var n = this,
                  i = [];
                return (
                  (r = r || this.jsoneditor.root.formname),
                  (t = f({}, this.jsoneditor.expandRefs(t))),
                  void 0 === e
                    ? this._validateV3Required(t, e, r)
                    : (Object.keys(t).forEach(function(o) {
                        n._validateSubSchema[o] && i.push.apply(i, O(n._validateSubSchema[o].call(n, t, e, r)));
                      }),
                      i.push.apply(i, O(this._validateByValueType(t, e, r))),
                      t.links &&
                        t.links.forEach(function(o, a) {
                          o.rel && 'describedby' === o.rel.toLowerCase() && ((t = n._expandSchemaLink(t, a)), i.push.apply(i, O(n._validateSchema(t, e, r, n.translate))));
                        }),
                      ['date', 'time', 'datetime-local'].includes(t.format) && i.push.apply(i, O(this._validateDateTimeSubSchema(t, e, r))),
                      ['uuid'].includes(t.format) && i.push.apply(i, O(this._validateUUIDSchema(t, e, r))),
                      i.push.apply(i, O(this._validateCustomValidator(t, e, r))),
                      this._removeDuplicateErrors(i))
                );
              },
            },
            {
              key: '_expandSchemaLink',
              value: function(t, e) {
                var r = t.links[e].href,
                  n = this.jsoneditor.root.getValue(),
                  i = this.jsoneditor.compileTemplate(r, this.jsoneditor.template),
                  o = document.location.origin + document.location.pathname + i(n);
                return (t.links = t.links.slice(0, e).concat(t.links.slice(e + 1))), f({}, t, this.jsoneditor.refs[o]);
              },
            },
            {
              key: '_validateV3Required',
              value: function(t, e, r) {
                return ((void 0 !== t.required && !0 === t.required) || (void 0 === t.required && !0 === this.jsoneditor.options.required_by_default)) && 'info' !== t.type
                  ? [{ path: r, property: 'required', message: this.translate('error_notset') }]
                  : [];
              },
            },
            {
              key: '_validateByValueType',
              value: function(t, e, r) {
                var n = this,
                  i = [];
                if (null === e) return i;
                if ('number' == typeof e)
                  Object.keys(t).forEach(function(o) {
                    n._validateNumberSubSchema[o] && i.push.apply(i, O(n._validateNumberSubSchema[o].call(n, t, e, r)));
                  });
                else if ('string' == typeof e)
                  Object.keys(t).forEach(function(o) {
                    n._validateStringSubSchema[o] && i.push.apply(i, O(n._validateStringSubSchema[o].call(n, t, e, r)));
                  });
                else if (Array.isArray(e))
                  Object.keys(t).forEach(function(o) {
                    n._validateArraySubSchema[o] && i.push.apply(i, O(n._validateArraySubSchema[o].call(n, t, e, r)));
                  });
                else if ('object' === S(e)) {
                  var o = {};
                  Object.keys(t).forEach(function(a) {
                    n._validateObjectSubSchema[a] && i.push.apply(i, O(n._validateObjectSubSchema[a].call(n, t, e, r, o)));
                  }),
                    void 0 !== t.additionalProperties || !this.jsoneditor.options.no_additional_properties || t.oneOf || t.anyOf || t.allOf || (t.additionalProperties = !1),
                    Object.keys(t).forEach(function(a) {
                      void 0 !== n._validateObjectSubSchema2[a] && i.push.apply(i, O(n._validateObjectSubSchema2[a].call(n, t, e, r, o)));
                    });
                }
                return i;
              },
            },
            {
              key: '_validateUUIDSchema',
              value: function(t, e, r) {
                return /^[0-9a-f]{8}-[0-9a-f]{4}-[1-5][0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/i.test(e)
                  ? []
                  : [{ path: r, property: 'format', message: this.translate('error_pattern', ['^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$']) }];
              },
            },
            {
              key: '_validateNumberSubSchemaMultipleDivisible',
              value: function(t, e, r) {
                var n = t.multipleOf || t.divisibleBy,
                  i = e / n === Math.floor(e / n);
                return (
                  window.math
                    ? (i = window.math.mod(window.math.bignumber(e), window.math.bignumber(n)).equals(0))
                    : window.Decimal && (i = new window.Decimal(e).mod(new window.Decimal(n)).equals(0)),
                  i ? [] : [{ path: r, property: t.multipleOf ? 'multipleOf' : 'divisibleBy', message: this.translate('error_multipleOf', [n]) }]
                );
              },
            },
            {
              key: '_validateDateTimeSubSchema',
              value: function(t, e, r) {
                var n = this,
                  i = this.jsoneditor.getEditor(r),
                  o = i && i.flatpickr ? i.flatpickr.config.dateFormat : { date: '"YYYY-MM-DD"', time: '"HH:MM"', 'datetime-local': '"YYYY-MM-DD HH:MM"' }[t.format];
                if ('integer' === t.type)
                  return (function(t, e, r) {
                    return 1 * e < 1
                      ? [{ path: r, property: 'format', message: n.translate('error_invalid_epoch') }]
                      : e !== Math.abs(parseInt(e))
                      ? [{ path: r, property: 'format', message: n.translate('error_'.concat(t.format.replace(/-/g, '_')), [o]) }]
                      : [];
                  })(t, e, r);
                if (i && i.flatpickr) {
                  if (i)
                    return (function(t, e, r, i) {
                      if ('' !== e) {
                        var o;
                        if ('single' !== i.flatpickr.config.mode) {
                          var a = 'range' === i.flatpickr.config.mode ? i.flatpickr.l10n.rangeSeparator : ', ';
                          o = i.flatpickr.selectedDates
                            .map(function(t) {
                              return i.flatpickr.formatDate(t, i.flatpickr.config.dateFormat);
                            })
                            .join(a);
                        }
                        try {
                          if (o) {
                            if (o !== e) throw new Error(''.concat(i.flatpickr.config.mode, ' mismatch'));
                          } else if (i.flatpickr.formatDate(i.flatpickr.parseDate(e, i.flatpickr.config.dateFormat), i.flatpickr.config.dateFormat) !== e) throw new Error('mismatch');
                        } catch (t) {
                          var s = void 0 !== i.flatpickr.config.errorDateFormat ? i.flatpickr.config.errorDateFormat : i.flatpickr.config.dateFormat;
                          return [{ path: r, property: 'format', message: n.translate('error_'.concat(i.format.replace(/-/g, '_')), [s]) }];
                        }
                      }
                      return [];
                    })(0, e, r, i);
                } else if (!{ date: /^(\d{4}\D\d{2}\D\d{2})?$/, time: /^(\d{2}:\d{2}(?::\d{2})?)?$/, 'datetime-local': /^(\d{4}\D\d{2}\D\d{2}[ T]\d{2}:\d{2}(?::\d{2})?)?$/ }[t.format].test(e))
                  return [{ path: r, property: 'format', message: this.translate('error_'.concat(t.format.replace(/-/g, '_')), [o]) }];
                return [];
              },
            },
            {
              key: '_validateCustomValidator',
              value: function(t, e, r) {
                var n = this,
                  i = [];
                i.push.apply(i, O(u.call(this, t, e, r, this.translate)));
                var o = function(o) {
                  i.push.apply(i, O(o.call(n, t, e, r)));
                };
                return this.defaults.custom_validators.forEach(o), this.options.custom_validators && this.options.custom_validators.forEach(o), i;
              },
            },
            {
              key: '_removeDuplicateErrors',
              value: function(t) {
                return t.reduce(function(t, e) {
                  var r = !0;
                  return (
                    t || (t = []),
                    t.forEach(function(t) {
                      t.message === e.message && t.path === e.path && t.property === e.property && (t.errorcount++, (r = !1));
                    }),
                    r && ((e.errorcount = 1), t.push(e)),
                    t
                  );
                }, []);
              },
            },
            {
              key: '_checkType',
              value: function(t, e) {
                var r = {
                  string: function(t) {
                    return 'string' == typeof t;
                  },
                  number: function(t) {
                    return 'number' == typeof t;
                  },
                  integer: function(t) {
                    return 'number' == typeof t && t === Math.floor(t);
                  },
                  boolean: function(t) {
                    return 'boolean' == typeof t;
                  },
                  array: function(t) {
                    return Array.isArray(t);
                  },
                  object: function(t) {
                    return null !== t && !Array.isArray(t) && 'object' === S(t);
                  },
                  null: function(t) {
                    return null === t;
                  },
                };
                return 'string' == typeof t ? !r[t] || r[t](e) : !this._validateSchema(t, e).length;
              },
            },
          ]) && A(e.prototype, r),
          n && A(e, n),
          t
        );
      })();
      r(103), r(130), r(48);
      function T(t, e) {
        return (
          (function(t) {
            if (Array.isArray(t)) return t;
          })(t) ||
          (function(t, e) {
            var r = t && (('undefined' != typeof Symbol && t[Symbol.iterator]) || t['@@iterator']);
            if (null == r) return;
            var n,
              i,
              o = [],
              a = !0,
              s = !1;
            try {
              for (r = r.call(t); !(a = (n = r.next()).done) && (o.push(n.value), !e || o.length !== e); a = !0);
            } catch (t) {
              (s = !0), (i = t);
            } finally {
              try {
                a || null == r.return || r.return();
              } finally {
                if (s) throw i;
              }
            }
            return o;
          })(t, e) ||
          (function(t, e) {
            if (!t) return;
            if ('string' == typeof t) return R(t, e);
            var r = Object.prototype.toString.call(t).slice(8, -1);
            'Object' === r && t.constructor && (r = t.constructor.name);
            if ('Map' === r || 'Set' === r) return Array.from(t);
            if ('Arguments' === r || /^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(r)) return R(t, e);
          })(t, e) ||
          (function() {
            throw new TypeError('Invalid attempt to destructure non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.');
          })()
        );
      }
      function R(t, e) {
        (null == e || e > t.length) && (e = t.length);
        for (var r = 0, n = new Array(e); r < e; r++) n[r] = t[r];
        return n;
      }
      function I(t) {
        return (I =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function L(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      var N = (function() {
        function t(e) {
          !(function(t, e) {
            if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
          })(this, t),
            (this.options = e || {}),
            (this.refs = this.options.refs || {}),
            (this.refs_with_info = {}),
            (this.refs_prefix = '#/counter/'),
            (this.refs_counter = 1),
            (this._subSchema1 = {
              type: function(t) {
                'object' === I(t.type) && (t.type = this._expandSubSchema(t.type));
              },
              disallow: function(t) {
                'object' === I(t.disallow) && (t.disallow = this._expandSubSchema(t.disallow));
              },
              anyOf: function(t) {
                var e = this;
                Object.entries(t.anyOf).forEach(function(r) {
                  var n = T(r, 2),
                    i = n[0],
                    o = n[1];
                  t.anyOf[i] = e.expandSchema(o);
                });
              },
              dependencies: function(t) {
                var e = this;
                Object.entries(t.dependencies).forEach(function(r) {
                  var n = T(r, 2),
                    i = n[0],
                    o = n[1];
                  'object' !== I(o) || Array.isArray(o) || (t.dependencies[i] = e.expandSchema(o));
                });
              },
              not: function(t) {
                t.not = this.expandSchema(t.not);
              },
            }),
            (this._subSchema2 = {
              allOf: function(t, e) {
                var r = this,
                  n = f({}, e);
                return (
                  Object.entries(t.allOf).forEach(function(e) {
                    var i = T(e, 2),
                      o = i[0],
                      a = i[1];
                    (t.allOf[o] = r.expandRefs(a, !0)), (n = r.extendSchemas(n, r.expandSchema(a)));
                  }),
                  delete n.allOf,
                  n
                );
              },
              extends: function(t, e) {
                var r,
                  n = this;
                return (
                  delete (r = Array.isArray(t.extends)
                    ? t.extends.reduce(function(t, e, r) {
                        return n.extendSchemas(t, n.expandSchema(e));
                      }, e)
                    : this.extendSchemas(e, this.expandSchema(t.extends))).extends,
                  r
                );
              },
              oneOf: function(t, e) {
                var r = this,
                  n = f({}, e);
                return (
                  delete n.oneOf,
                  t.oneOf.reduce(function(t, e, i) {
                    return (t.oneOf[i] = r.extendSchemas(r.expandSchema(e), n)), t;
                  }, e),
                  e
                );
              },
            });
        }
        var e, r, n;
        return (
          (e = t),
          (r = [
            {
              key: 'load',
              value: function(t, e, r, n) {
                var i = this;
                this._loadExternalRefs(
                  t,
                  function() {
                    i._getDefinitions(t, ''.concat(r, '#/definitions/')), e(i.expandRefs(t));
                  },
                  r,
                  this._getFileBase(n)
                );
              },
            },
            {
              key: 'expandRefs',
              value: function(t, e) {
                var r = this,
                  n = f({}, t);
                if (!n.$ref) return n;
                var i = this.refs_with_info[n.$ref];
                delete n.$ref;
                var o = i.$ref.startsWith('#') ? i.fetchUrl : '',
                  a = this._getRef(o, i);
                if (this.refs[a]) {
                  if (e && v(this.refs[a], 'allOf')) {
                    var s = this.refs[a].allOf;
                    Object.keys(s).forEach(function(t) {
                      s[t] = r.expandRefs(s[t], !0);
                    });
                  }
                } else console.warn("reference:'".concat(a, "' not found!"));
                return this.extendSchemas(n, this.expandSchema(this.refs[a]));
              },
            },
            {
              key: 'expandSchema',
              value: function(t, e) {
                var r = this;
                Object.entries(this._subSchema1).forEach(function(e) {
                  var n = T(e, 2),
                    i = n[0],
                    o = n[1];
                  t[i] && o.call(r, t);
                });
                var n = f({}, t);
                return (
                  Object.entries(this._subSchema2).forEach(function(e) {
                    var i = T(e, 2),
                      o = i[0],
                      a = i[1];
                    t[o] && (n = a.call(r, t, n));
                  }),
                  this.expandRefs(n)
                );
              },
            },
            {
              key: '_getRef',
              value: function(t, e) {
                var r = t + e;
                return this.refs[r] ? r : t + decodeURIComponent(e.$ref);
              },
            },
            {
              key: '_expandSubSchema',
              value: function(t) {
                var e = this;
                return Array.isArray(t)
                  ? t.map(function(t) {
                      return 'object' === I(t) ? e.expandSchema(t) : t;
                    })
                  : this.expandSchema(t);
              },
            },
            {
              key: '_getDefinitions',
              value: function(t, e) {
                var r = this;
                t.definitions &&
                  Object.keys(t.definitions).forEach(function(n) {
                    (r.refs[e + n] = t.definitions[n]), t.definitions[n].definitions && r._getDefinitions(t.definitions[n], ''.concat(e + n, '/definitions/'));
                  });
              },
            },
            {
              key: '_getExternalRefs',
              value: function(t, e) {
                var r = this,
                  n = {},
                  i = function(t) {
                    return Object.keys(t).forEach(function(t) {
                      n[t] = !0;
                    });
                  };
                if (t.$ref && 'object' !== I(t.$ref)) {
                  var o = this.refs_prefix + this.refs_counter++;
                  '#' === t.$ref.substr(0, 1) || this.refs[t.$ref] || (n[t.$ref] = !0), (this.refs_with_info[o] = { fetchUrl: e, $ref: t.$ref }), (t.$ref = o);
                }
                return (
                  Object.values(t).forEach(function(t) {
                    t &&
                      'object' === I(t) &&
                      (Array.isArray(t)
                        ? Object.values(t).forEach(function(t) {
                            t && 'object' === I(t) && i(r._getExternalRefs(t, e));
                          })
                        : i(r._getExternalRefs(t, e)));
                  }),
                  t.id && 'string' == typeof t.id && 'urn:' === t.id.substr(0, 4)
                    ? (this.refs[t.id] = t)
                    : t.$id && 'string' == typeof t.$id && 'urn:' === t.$id.substr(0, 4) && (this.refs[t.$id] = t),
                  n
                );
              },
            },
            {
              key: '_getFileBase',
              value: function(t) {
                if (!t) return '/';
                var e = this.options.ajaxBase;
                return void 0 === e ? this._getFileBaseFromFileLocation(t) : e;
              },
            },
            {
              key: '_getFileBaseFromFileLocation',
              value: function(t) {
                var e = t.split('/');
                return e.pop(), ''.concat(e.join('/'), '/');
              },
            },
            {
              key: '_joinUrl',
              value: function(t, e) {
                var r = t;
                return (
                  'http://' !== t.substr(0, 7) &&
                    'https://' !== t.substr(0, 8) &&
                    'blob:' !== t.substr(0, 5) &&
                    'data:' !== t.substr(0, 5) &&
                    '#' !== t.substr(0, 1) &&
                    '/' !== t.substr(0, 1) &&
                    (r = e + t),
                  r.indexOf('#') > 0 && (r = r.substr(0, r.indexOf('#'))),
                  r
                );
              },
            },
            {
              key: '_isUniformResourceName',
              value: function(t) {
                return 'urn:' === t.substr(0, 4);
              },
            },
            {
              key: '_loadExternalRefs',
              value: function(t, e, r, n) {
                var i = this,
                  o = this._getExternalRefs(t, r),
                  a = !1,
                  s = 0;
                Object.keys(o).forEach(function(r) {
                  if (!i.refs[r])
                    if (i._isUniformResourceName(r)) {
                      (i.refs[r] = 'loading'), s++;
                      var o,
                        l = i.options.urn_resolver,
                        c = r;
                      if ('function' != typeof l)
                        throw (console.log('No "urn_resolver" callback defined to resolve "'.concat(c, '"')), new Error('Must set urn_resolver option to a callback to resolve '.concat(c)));
                      c.indexOf('#') > 0 && (c = c.substr(0, c.indexOf('#')));
                      try {
                        o = l(c, function(n) {
                          try {
                            t = JSON.parse(n);
                          } catch (t) {
                            throw (console.log(t), new Error('Failed to parse external ref '.concat(c)));
                          }
                          if (('boolean' != typeof t && 'object' !== I(t)) || null === t || Array.isArray(t)) throw new Error('External ref does not contain a valid schema - '.concat(c));
                          (i.refs[r] = t),
                            i._getDefinitions(t, ''.concat(c, '#/definitions/')),
                            i._loadExternalRefs(
                              t,
                              function() {
                                s--, a && !s && e();
                              },
                              r,
                              '/'
                            );
                        });
                      } catch (t) {
                        throw (console.log(t), new Error('Failed to parse external ref '.concat(c)));
                      }
                      if ('boolean' != typeof o) throw new Error('External ref does not contain a valid schema - '.concat(c));
                      if (!0 !== o) throw new Error('External ref did not resolve - '.concat(c));
                    } else {
                      if (!i.options.ajax) throw new Error('Must set ajax option to true to load external ref '.concat(r));
                      (i.refs[r] = 'loading'), s++;
                      var u = i._joinUrl(r, n),
                        h = new XMLHttpRequest();
                      h.overrideMimeType('application/json'),
                        h.open('GET', u, !0),
                        i.options.ajaxCredentials && (h.withCredentials = i.options.ajaxCredentials),
                        (h.onreadystatechange = function() {
                          if (4 === h.readyState) {
                            if (200 !== h.status) throw (console.log(h), new Error('Failed to fetch ref via ajax - '.concat(r)));
                            var t;
                            try {
                              t = JSON.parse(h.responseText);
                            } catch (t) {
                              throw (console.log(t), new Error('Failed to parse external ref '.concat(u)));
                            }
                            if (('boolean' != typeof t && 'object' !== I(t)) || null === t || Array.isArray(t)) throw new Error('External ref does not contain a valid schema - '.concat(u));
                            i.refs[r] = t;
                            var n = i._getFileBaseFromFileLocation(u);
                            if (u !== r) {
                              var o = u.split('/');
                              u = ('/' === r.substr(0, 1) ? '/' : '') + o.pop();
                            }
                            i._getDefinitions(t, ''.concat(u, '#/definitions/')),
                              i._loadExternalRefs(
                                t,
                                function() {
                                  s--, a && !s && e();
                                },
                                u,
                                n
                              );
                          }
                        }),
                        h.send();
                    }
                }),
                  (a = !0),
                  s || e();
              },
            },
            {
              key: 'extendSchemas',
              value: function(t, e) {
                var r = this;
                (t = f({}, t)), (e = f({}, e));
                var n = {},
                  i = function(t, i) {
                    !(function(t, e) {
                      return ('required' === t || 'defaultProperties' === t) && 'object' === I(e) && Array.isArray(e);
                    })(t, i)
                      ? 'type' !== t || ('string' != typeof i && !Array.isArray(i))
                        ? 'object' !== I(i) || Array.isArray(i) || null === i
                          ? (n[t] = i)
                          : (n[t] = r.extendSchemas(i, e[t]))
                        : o(i)
                      : (n[t] = i.concat(e[t]).reduce(function(t, e) {
                          return t.includes(e) || t.push(e), t;
                        }, []));
                  },
                  o = function(t) {
                    'string' == typeof t && (t = [t]),
                      'string' == typeof e.type && (e.type = [e.type]),
                      e.type && e.type.length
                        ? (n.type = t.filter(function(t) {
                            return e.type.includes(t);
                          }))
                        : (n.type = t),
                      1 === n.type.length && 'string' == typeof n.type[0] ? (n.type = n.type[0]) : 0 === n.type.length && delete n.type;
                  };
                return (
                  Object.entries(t).forEach(function(t) {
                    var r = T(t, 2),
                      o = r[0],
                      a = r[1];
                    void 0 !== e[o] ? i(o, a) : (n[o] = a);
                  }),
                  Object.entries(e).forEach(function(e) {
                    var r = T(e, 2),
                      i = r[0],
                      o = r[1];
                    void 0 === t[i] && (n[i] = o);
                  }),
                  n
                );
              },
            },
          ]) && L(e.prototype, r),
          n && L(e, n),
          t
        );
      })();
      r(21), r(22), r(23), r(24), r(30), r(132);
      function B(t, e) {
        return (
          (function(t) {
            if (Array.isArray(t)) return t;
          })(t) ||
          (function(t, e) {
            var r = t && (('undefined' != typeof Symbol && t[Symbol.iterator]) || t['@@iterator']);
            if (null == r) return;
            var n,
              i,
              o = [],
              a = !0,
              s = !1;
            try {
              for (r = r.call(t); !(a = (n = r.next()).done) && (o.push(n.value), !e || o.length !== e); a = !0);
            } catch (t) {
              (s = !0), (i = t);
            } finally {
              try {
                a || null == r.return || r.return();
              } finally {
                if (s) throw i;
              }
            }
            return o;
          })(t, e) ||
          (function(t, e) {
            if (!t) return;
            if ('string' == typeof t) return V(t, e);
            var r = Object.prototype.toString.call(t).slice(8, -1);
            'Object' === r && t.constructor && (r = t.constructor.name);
            if ('Map' === r || 'Set' === r) return Array.from(t);
            if ('Arguments' === r || /^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(r)) return V(t, e);
          })(t, e) ||
          (function() {
            throw new TypeError('Invalid attempt to destructure non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.');
          })()
        );
      }
      function V(t, e) {
        (null == e || e > t.length) && (e = t.length);
        for (var r = 0, n = new Array(e); r < e; r++) n[r] = t[r];
        return n;
      }
      function D(t) {
        return (D =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function F(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      var M = (function() {
        function t(e, r) {
          !(function(t, e) {
            if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
          })(this, t),
            (this.defaults = r),
            (this.jsoneditor = e.jsoneditor),
            (this.theme = this.jsoneditor.theme),
            (this.template_engine = this.jsoneditor.template),
            (this.iconlib = this.jsoneditor.iconlib),
            (this.translate = this.jsoneditor.translate || this.defaults.translate),
            (this.translateProperty = this.jsoneditor.translateProperty || this.defaults.translateProperty),
            (this.original_schema = e.schema),
            (this.schema = this.jsoneditor.expandSchema(this.original_schema)),
            (this.active = !0),
            (this.options = f({}, this.options || {}, this.schema.options || {}, e.schema.options || {}, e)),
            (this.formname = this.jsoneditor.options.form_name_root || 'root'),
            e.path || this.schema.id || (this.schema.id = this.formname),
            (this.path = e.path || this.formname),
            (this.template_path = e.template_path || ''),
            (this.formname = e.formname || this.path.replace(/\.([^.]+)/g, '[$1]')),
            (this.parent = e.parent),
            (this.key =
              void 0 !== this.parent
                ? this.path
                    .split('.')
                    .slice(this.parent.path.split('.').length)
                    .join('.')
                : this.path),
            (this.link_watchers = []),
            (this.watchLoop = !1),
            e.container && this.setContainer(e.container),
            this.registerDependencies();
        }
        var e, r, n;
        return (
          (e = t),
          (r = [
            {
              key: 'onChildEditorChange',
              value: function(t) {
                this.onChange(!0);
              },
            },
            {
              key: 'notify',
              value: function() {
                this.path && this.jsoneditor.notifyWatchers(this.path);
              },
            },
            {
              key: 'change',
              value: function() {
                this.parent ? this.parent.onChildEditorChange(this) : this.jsoneditor && this.jsoneditor.onChange();
              },
            },
            {
              key: 'onChange',
              value: function(t) {
                this.notify(), this.watch_listener && this.watch_listener(), t && this.change();
              },
            },
            {
              key: 'register',
              value: function() {
                this.jsoneditor.registerEditor(this), this.onChange();
              },
            },
            {
              key: 'unregister',
              value: function() {
                this.jsoneditor && this.jsoneditor.unregisterEditor(this);
              },
            },
            {
              key: 'getNumColumns',
              value: function() {
                return 12;
              },
            },
            {
              key: 'isActive',
              value: function() {
                return this.active;
              },
            },
            {
              key: 'activate',
              value: function() {
                (this.active = !0), (this.optInCheckbox.checked = !0), this.enable(), this.change();
              },
            },
            {
              key: 'deactivate',
              value: function() {
                this.isRequired() || ((this.active = !1), (this.optInCheckbox.checked = !1), this.disable(), this.change());
              },
            },
            {
              key: 'registerDependencies',
              value: function() {
                var t = this;
                this.dependenciesFulfilled = !0;
                var e = this.options.dependencies;
                e &&
                  Object.keys(e).forEach(function(e) {
                    var r = t.path.split('.');
                    (r[r.length - 1] = e),
                      (r = r.join('.')),
                      t.jsoneditor.watch(r, function() {
                        t.evaluateDependencies();
                      });
                  });
              },
            },
            {
              key: 'evaluateDependencies',
              value: function() {
                var t = this,
                  e = this.container || this.control;
                if (e && null !== this.jsoneditor) {
                  var r = this.options.dependencies;
                  if (r) {
                    var n = this.dependenciesFulfilled;
                    (this.dependenciesFulfilled = !0),
                      Object.keys(r).forEach(function(e) {
                        var n = t.path.split('.');
                        (n[n.length - 1] = e), (n = n.join('.'));
                        var i = r[e];
                        t.checkDependency(n, i);
                      }),
                      this.dependenciesFulfilled !== n && this.notify();
                    var i = this.dependenciesFulfilled ? 'block' : 'none';
                    this.options.hidden && (i = 'none'),
                      'TD' === e.tagName
                        ? Object.keys(e.childNodes).forEach(function(t) {
                            return (e.childNodes[t].style.display = i);
                          })
                        : (e.style.display = i);
                  }
                }
              },
            },
            {
              key: 'checkDependency',
              value: function(t, e) {
                var r = this;
                if (this.path !== t && null !== this.jsoneditor) {
                  var n = this.jsoneditor.getEditor(t),
                    i = n ? n.getValue() : void 0;
                  n && n.dependenciesFulfilled
                    ? Array.isArray(e)
                      ? (this.dependenciesFulfilled = e.some(function(t) {
                          if (JSON.stringify(i) === JSON.stringify(t)) return !0;
                        }))
                      : 'object' === D(e)
                      ? 'object' !== D(i)
                        ? (this.dependenciesFulfilled = e === i)
                        : Object.keys(e).some(function(t) {
                            return !!v(e, t) && (v(i, t) && e[t] === i[t] ? void 0 : ((r.dependenciesFulfilled = !1), !0));
                          })
                      : 'string' == typeof e || 'number' == typeof e
                      ? (this.dependenciesFulfilled = this.dependenciesFulfilled && i === e)
                      : 'boolean' == typeof e && (this.dependenciesFulfilled = e ? this.dependenciesFulfilled && (i || i.length > 0) : this.dependenciesFulfilled && (!i || 0 === i.length))
                    : (this.dependenciesFulfilled = !1);
                }
              },
            },
            {
              key: 'setContainer',
              value: function(t) {
                (this.container = t),
                  this.schema.id && this.container.setAttribute('data-schemaid', this.schema.id),
                  this.schema.type && 'string' == typeof this.schema.type && this.container.setAttribute('data-schematype', this.schema.type),
                  this.container.setAttribute('data-schemapath', this.path),
                  this.template_path && ':' !== this.template_path.slice(-1) && this.container.setAttribute('data-template-path', this.template_path);
              },
            },
            {
              key: 'setOptInCheckbox',
              value: function(t) {
                var e = this;
                (this.optInCheckbox = document.createElement('input')),
                  this.optInCheckbox.setAttribute('type', 'checkbox'),
                  this.optInCheckbox.setAttribute('style', 'margin: 0 10px 0 0;'),
                  this.optInCheckbox.classList.add('json-editor-opt-in'),
                  this.optInCheckbox.addEventListener('click', function() {
                    e.isActive() ? e.deactivate() : e.activate();
                  });
                var r = this.jsoneditor.options.show_opt_in,
                  n = void 0 !== this.parent.options.show_opt_in,
                  i = n && !0 === this.parent.options.show_opt_in,
                  o = n && !1 === this.parent.options.show_opt_in;
                (i || (!o && r) || (!n && r)) &&
                  this.parent &&
                  'object' === this.parent.schema.type &&
                  !this.isRequired() &&
                  this.header &&
                  (this.header.appendChild(this.optInCheckbox), this.header.insertBefore(this.optInCheckbox, this.header.firstChild));
              },
            },
            { key: 'preBuild', value: function() {} },
            { key: 'build', value: function() {} },
            {
              key: 'postBuild',
              value: function() {
                this.setupWatchListeners(), this.addLinks(), this.setValue(this.getDefault(), !0), this.updateHeaderText(), this.register(), this.onWatchedFieldChange();
              },
            },
            {
              key: 'setupWatchListeners',
              value: function() {
                var t = this;
                if (
                  ((this.watched = {}),
                  this.schema.vars && (this.schema.watch = this.schema.vars),
                  (this.watched_values = {}),
                  (this.watch_listener = function() {
                    t.refreshWatchedFieldValues() && t.onWatchedFieldChange();
                  }),
                  v(this.schema, 'watch'))
                ) {
                  var e,
                    r,
                    n,
                    i,
                    o,
                    a = this.container.getAttribute('data-schemapath');
                  Object.keys(this.schema.watch).forEach(function(s) {
                    if (((e = t.schema.watch[s]), Array.isArray(e))) {
                      if (e.length < 2) return;
                      r = [e[0]].concat(e[1].split('.'));
                    } else (r = e.split('.')), t.theme.closest(t.container, '[data-schemaid="'.concat(r[0], '"]')) || r.unshift('#');
                    if (('#' === (n = r.shift()) && (n = t.jsoneditor.schema.id || t.jsoneditor.root.formname), !(i = t.theme.closest(t.container, '[data-schemaid="'.concat(n, '"]')))))
                      throw new Error('Could not find ancestor node with id '.concat(n));
                    (o = ''.concat(i.getAttribute('data-schemapath'), '.').concat(r.join('.'))), a.startsWith(o) && (t.watchLoop = !0), t.jsoneditor.watch(o, t.watch_listener), (t.watched[s] = o);
                  });
                }
                this.schema.headerTemplate && (this.header_template = this.jsoneditor.compileTemplate(this.schema.headerTemplate, this.template_engine));
              },
            },
            {
              key: 'addLinks',
              value: function() {
                if (
                  !this.no_link_holder &&
                  ((this.link_holder = this.theme.getLinksHolder()),
                  void 0 !== this.description ? this.description.parentNode.insertBefore(this.link_holder, this.description) : this.container.appendChild(this.link_holder),
                  this.schema.links)
                )
                  for (var t = 0; t < this.schema.links.length; t++) this.addLink(this.getLink(this.schema.links[t]));
              },
            },
            { key: 'onMove', value: function() {} },
            {
              key: 'getButton',
              value: function(t, e, r) {
                var n = arguments.length > 3 && void 0 !== arguments[3] ? arguments[3] : [],
                  i = 'json-editor-btn-'.concat(e);
                (e = this.iconlib ? this.iconlib.getIcon(e) : null), (t = this.translate(t, n)), (r = this.translate(r, n)), !e && r && ((t = r), (r = null));
                var o = this.theme.getButton(t, e, r);
                return o.classList.add(i), o;
              },
            },
            {
              key: 'setButtonText',
              value: function(t, e, r, n) {
                var i = arguments.length > 4 && void 0 !== arguments[4] ? arguments[4] : [];
                return (
                  (r = this.iconlib ? this.iconlib.getIcon(r) : null), (e = this.translate(e, i)), (n = this.translate(n, i)), !r && n && ((e = n), (n = null)), this.theme.setButtonText(t, e, r, n)
                );
              },
            },
            {
              key: 'addLink',
              value: function(t) {
                this.link_holder && this.link_holder.appendChild(t);
              },
            },
            {
              key: 'getLink',
              value: function(t) {
                var e,
                  r,
                  n = (t.mediaType || 'application/javascript').split('/')[0],
                  i = this.jsoneditor.compileTemplate(t.href, this.template_engine),
                  o = this.jsoneditor.compileTemplate(t.rel ? t.rel : t.href, this.template_engine),
                  a = null;
                if ((t.download && (a = t.download), a && !0 !== a && (a = this.jsoneditor.compileTemplate(a, this.template_engine)), 'image' === n)) {
                  (e = this.theme.getBlockLinkHolder()), (r = document.createElement('a')).setAttribute('target', '_blank');
                  var s = document.createElement('img');
                  this.theme.createImageLink(e, r, s),
                    this.link_watchers.push(function(t) {
                      var e = i(t),
                        n = o(t);
                      r.setAttribute('href', e), r.setAttribute('title', n || e), s.setAttribute('src', e);
                    });
                } else if (['audio', 'video'].includes(n)) {
                  (e = this.theme.getBlockLinkHolder()), (r = this.theme.getBlockLink()).setAttribute('target', '_blank');
                  var l = document.createElement(n);
                  l.setAttribute('controls', 'controls'),
                    this.theme.createMediaLink(e, r, l),
                    this.link_watchers.push(function(t) {
                      var e = i(t),
                        n = o(t);
                      r.setAttribute('href', e), (r.textContent = n || e), l.setAttribute('src', e);
                    });
                } else
                  (r = e = this.theme.getBlockLink()),
                    e.setAttribute('target', '_blank'),
                    (e.textContent = t.rel),
                    (e.style.display = 'none'),
                    this.link_watchers.push(function(t) {
                      var r = i(t),
                        n = o(t);
                      r && (e.style.display = ''), e.setAttribute('href', r), (e.textContent = n || r);
                    });
                return (
                  a &&
                    r &&
                    (!0 === a
                      ? r.setAttribute('download', '')
                      : this.link_watchers.push(function(t) {
                          r.setAttribute('download', a(t));
                        })),
                  t.class && r.classList.add(t.class),
                  e
                );
              },
            },
            {
              key: 'refreshWatchedFieldValues',
              value: function() {
                var t = this;
                if (this.watched_values) {
                  var e = {},
                    r = !1;
                  return (
                    this.watched &&
                      Object.keys(this.watched).forEach(function(n) {
                        var i = t.jsoneditor.getEditor(t.watched[n]),
                          o = i ? i.getValue() : null;
                        t.watched_values[n] !== o && (r = !0), (e[n] = o);
                      }),
                    (e.self = this.getValue()),
                    this.watched_values.self !== e.self && (r = !0),
                    (this.watched_values = e),
                    r
                  );
                }
              },
            },
            {
              key: 'getWatchedFieldValues',
              value: function() {
                return this.watched_values;
              },
            },
            {
              key: 'updateHeaderText',
              value: function() {
                if (this.header) {
                  var t = this.getHeaderText();
                  if (this.header.children.length) {
                    for (var e = 0; e < this.header.childNodes.length; e++)
                      if (3 === this.header.childNodes[e].nodeType) {
                        this.header.childNodes[e].nodeValue = this.cleanText(t);
                        break;
                      }
                  } else window.DOMPurify ? (this.header.innerHTML = window.DOMPurify.sanitize(t)) : (this.header.textContent = this.cleanText(t));
                }
              },
            },
            {
              key: 'getHeaderText',
              value: function(t) {
                return this.header_text ? this.header_text : t ? this.translateProperty(this.schema.title) : this.getTitle();
              },
            },
            {
              key: 'getPathDepth',
              value: function() {
                return this.path.split('.').length;
              },
            },
            {
              key: 'cleanText',
              value: function(t) {
                var e = document.createElement('div');
                return (e.innerHTML = t), e.textContent || e.innerText;
              },
            },
            {
              key: 'onWatchedFieldChange',
              value: function() {
                var t;
                if (this.header_template) {
                  t = f(this.getWatchedFieldValues(), { key: this.key, i: this.key, i0: 1 * this.key, i1: 1 * this.key + 1, title: this.getTitle() });
                  var e = this.header_template(t);
                  e !== this.header_text && ((this.header_text = e), this.updateHeaderText(), this.notify());
                }
                if (this.link_watchers.length) {
                  t = this.getWatchedFieldValues();
                  for (var r = 0; r < this.link_watchers.length; r++) this.link_watchers[r](t);
                }
              },
            },
            {
              key: 'setValue',
              value: function(t) {
                this.value = t;
              },
            },
            {
              key: 'getValue',
              value: function() {
                if (this.dependenciesFulfilled) return this.value;
              },
            },
            { key: 'refreshValue', value: function() {} },
            {
              key: 'getChildEditors',
              value: function() {
                return !1;
              },
            },
            {
              key: 'destroy',
              value: function() {
                var t = this;
                this.unregister(this),
                  this.watched &&
                    Object.values(this.watched).forEach(function(e) {
                      return t.jsoneditor.unwatch(e, t.watch_listener);
                    }),
                  (this.watched = null),
                  (this.watched_values = null),
                  (this.watch_listener = null),
                  (this.header_text = null),
                  (this.header_template = null),
                  (this.value = null),
                  this.container && this.container.parentNode && this.container.parentNode.removeChild(this.container),
                  (this.container = null),
                  (this.jsoneditor = null),
                  (this.schema = null),
                  (this.path = null),
                  (this.key = null),
                  (this.parent = null);
              },
            },
            {
              key: 'isDefaultRequired',
              value: function() {
                return this.isRequired() || !!this.jsoneditor.options.use_default_values;
              },
            },
            {
              key: 'getDefault',
              value: function() {
                if (void 0 !== this.schema.default) return this.schema.default;
                if (void 0 !== this.schema.enum) return this.schema.enum[0];
                var t = this.schema.type || this.schema.oneOf;
                if ((t && Array.isArray(t) && (t = t[0]), t && 'object' === D(t) && (t = t.type), t && Array.isArray(t) && (t = t[0]), 'string' == typeof t)) {
                  if ('number' === t) return this.isDefaultRequired() ? 0 : void 0;
                  if ('boolean' === t) return !this.isDefaultRequired() && void 0;
                  if ('integer' === t) return this.isDefaultRequired() ? 0 : void 0;
                  if ('string' === t) return '';
                  if ('object' === t) return {};
                  if ('array' === t) return [];
                }
                return null;
              },
            },
            {
              key: 'getTitle',
              value: function() {
                return this.translateProperty(this.schema.title || this.key);
              },
            },
            {
              key: 'enable',
              value: function() {
                this.disabled = !1;
              },
            },
            {
              key: 'disable',
              value: function() {
                this.disabled = !0;
              },
            },
            {
              key: 'isEnabled',
              value: function() {
                return !this.disabled;
              },
            },
            {
              key: 'isRequired',
              value: function() {
                return 'boolean' == typeof this.schema.required
                  ? this.schema.required
                  : this.parent && this.parent.schema && Array.isArray(this.parent.schema.required)
                  ? this.parent.schema.required.includes(this.key)
                  : !!this.jsoneditor.options.required_by_default;
              },
            },
            {
              key: 'getDisplayText',
              value: function(t) {
                var e = [],
                  r = {};
                t.forEach(function(t) {
                  t.title && ((r[t.title] = r[t.title] || 0), r[t.title]++),
                    t.description && ((r[t.description] = r[t.description] || 0), r[t.description]++),
                    t.format && ((r[t.format] = r[t.format] || 0), r[t.format]++),
                    t.type && ((r[t.type] = r[t.type] || 0), r[t.type]++);
                }),
                  t.forEach(function(t) {
                    var n;
                    (n =
                      'string' == typeof t
                        ? t
                        : t.title && r[t.title] <= 1
                        ? t.title
                        : t.format && r[t.format] <= 1
                        ? t.format
                        : t.type && r[t.type] <= 1
                        ? t.type
                        : t.description && r[t.description] <= 1
                        ? t.descripton
                        : t.title
                        ? t.title
                        : t.format
                        ? t.format
                        : t.type
                        ? t.type
                        : t.description
                        ? t.description
                        : JSON.stringify(t).length < 500
                        ? JSON.stringify(t)
                        : 'type'),
                      e.push(n);
                  });
                var n = {};
                return (
                  e.forEach(function(t, i) {
                    (n[t] = n[t] || 0), n[t]++, r[t] > 1 && (e[i] = ''.concat(t, ' ').concat(n[t]));
                  }),
                  e
                );
              },
            },
            {
              key: 'getValidId',
              value: function(t) {
                return (t = void 0 === t ? '' : t.toString()).replace(/\s+/g, '-');
              },
            },
            {
              key: 'setInputAttributes',
              value: function(t) {
                var e = this;
                if (this.schema.options && this.schema.options.inputAttributes) {
                  var r = this.schema.options.inputAttributes,
                    n = ['name', 'type'].concat(t);
                  Object.keys(r).forEach(function(t) {
                    n.includes(t.toLowerCase()) || e.input.setAttribute(t, r[t]);
                  });
                }
              },
            },
            {
              key: 'expandCallbacks',
              value: function(t, e) {
                var r = this,
                  n = this.defaults.callbacks[t];
                return (
                  Object.entries(e).forEach(function(i) {
                    var o = B(i, 2),
                      a = o[0],
                      s = o[1];
                    s === Object(s) ? (e[a] = r.expandCallbacks(t, s)) : 'string' == typeof s && 'object' === D(n) && 'function' == typeof n[s] && (e[a] = n[s].bind(null, r));
                  }),
                  e
                );
              },
            },
            { key: 'showValidationErrors', value: function(t) {} },
          ]) && F(e.prototype, r),
          n && F(e, n),
          t
        );
      })();
      function H(t) {
        return (H =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function q(t, e) {
        if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
      }
      function U(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      function z(t, e, r) {
        return (z =
          'undefined' != typeof Reflect && Reflect.get
            ? Reflect.get
            : function(t, e, r) {
                var n = (function(t, e) {
                  for (; !Object.prototype.hasOwnProperty.call(t, e) && null !== (t = W(t)); );
                  return t;
                })(t, e);
                if (n) {
                  var i = Object.getOwnPropertyDescriptor(n, e);
                  return i.get ? i.get.call(r) : i.value;
                }
              })(t, e, r || t);
      }
      function $(t, e) {
        return ($ =
          Object.setPrototypeOf ||
          function(t, e) {
            return (t.__proto__ = e), t;
          })(t, e);
      }
      function J(t) {
        var e = (function() {
          if ('undefined' == typeof Reflect || !Reflect.construct) return !1;
          if (Reflect.construct.sham) return !1;
          if ('function' == typeof Proxy) return !0;
          try {
            return Boolean.prototype.valueOf.call(Reflect.construct(Boolean, [], function() {})), !0;
          } catch (t) {
            return !1;
          }
        })();
        return function() {
          var r,
            n = W(t);
          if (e) {
            var i = W(this).constructor;
            r = Reflect.construct(n, arguments, i);
          } else r = n.apply(this, arguments);
          return G(this, r);
        };
      }
      function G(t, e) {
        return !e || ('object' !== H(e) && 'function' != typeof e)
          ? (function(t) {
              if (void 0 === t) throw new ReferenceError("this hasn't been initialised - super() hasn't been called");
              return t;
            })(t)
          : e;
      }
      function W(t) {
        return (W = Object.setPrototypeOf
          ? Object.getPrototypeOf
          : function(t) {
              return t.__proto__ || Object.getPrototypeOf(t);
            })(t);
      }
      var Y = (function(t) {
        !(function(t, e) {
          if ('function' != typeof e && null !== e) throw new TypeError('Super expression must either be null or a function');
          (t.prototype = Object.create(e && e.prototype, { constructor: { value: t, writable: !0, configurable: !0 } })), e && $(t, e);
        })(o, t);
        var e,
          r,
          n,
          i = J(o);
        function o() {
          return q(this, o), i.apply(this, arguments);
        }
        return (
          (e = o),
          (r = [
            {
              key: 'askConfirmation',
              value: function() {
                return !0 !== this.jsoneditor.options.prompt_before_delete || !1 !== window.confirm(this.translate('button_delete_node_warning'));
              },
            },
            {
              key: 'getDefault',
              value: function() {
                return this.schema.default || [];
              },
            },
            {
              key: 'register',
              value: function() {
                z(W(o.prototype), 'register', this).call(this),
                  this.rows &&
                    this.rows.forEach(function(t) {
                      return t.register();
                    });
              },
            },
            {
              key: 'unregister',
              value: function() {
                z(W(o.prototype), 'unregister', this).call(this),
                  this.rows &&
                    this.rows.forEach(function(t) {
                      return t.unregister();
                    });
              },
            },
            {
              key: 'getNumColumns',
              value: function() {
                var t = this.getItemInfo(0);
                return this.tabs_holder && 'tabs-top' !== this.schema.format ? Math.max(Math.min(12, t.width + 2), 4) : t.width;
              },
            },
            {
              key: 'enable',
              value: function() {
                var t = this;
                this.always_disabled ||
                  (this.setAvailability(this, !1),
                  this.rows &&
                    this.rows.forEach(function(e) {
                      e.enable(), t.setAvailability(e, !1);
                    }),
                  z(W(o.prototype), 'enable', this).call(this));
              },
            },
            {
              key: 'disable',
              value: function(t) {
                var e = this;
                t && (this.always_disabled = !0),
                  this.setAvailability(this, !0),
                  this.rows &&
                    this.rows.forEach(function(r) {
                      r.disable(t), e.setAvailability(r, !0);
                    }),
                  z(W(o.prototype), 'disable', this).call(this);
              },
            },
            {
              key: 'setAvailability',
              value: function(t, e) {
                t.add_row_button && (t.add_row_button.disabled = e),
                  t.remove_all_rows_button && (t.remove_all_rows_button.disabled = e),
                  t.delete_last_row_button && (t.delete_last_row_button.disabled = e),
                  t.copy_button && (t.copy_button.disabled = e),
                  t.delete_button && (t.delete_button.disabled = e),
                  t.moveup_button && (t.moveup_button.disabled = e),
                  t.movedown_button && (t.movedown_button.disabled = e);
              },
            },
            {
              key: 'preBuild',
              value: function() {
                z(W(o.prototype), 'preBuild', this).call(this),
                  (this.rows = []),
                  (this.row_cache = []),
                  (this.hide_delete_buttons = this.options.disable_array_delete || this.jsoneditor.options.disable_array_delete),
                  (this.hide_delete_all_rows_buttons = this.hide_delete_buttons || this.options.disable_array_delete_all_rows || this.jsoneditor.options.disable_array_delete_all_rows),
                  (this.hide_delete_last_row_buttons = this.hide_delete_buttons || this.options.disable_array_delete_last_row || this.jsoneditor.options.disable_array_delete_last_row),
                  (this.hide_move_buttons = this.options.disable_array_reorder || this.jsoneditor.options.disable_array_reorder),
                  (this.hide_add_button = this.options.disable_array_add || this.jsoneditor.options.disable_array_add),
                  (this.show_copy_button = this.options.enable_array_copy || this.jsoneditor.options.enable_array_copy),
                  (this.array_controls_top = this.options.array_controls_top || this.jsoneditor.options.array_controls_top);
              },
            },
            {
              key: 'build',
              value: function() {
                if (this.options.compact)
                  (this.title = this.theme.getHeader('', this.getPathDepth())),
                    this.container.appendChild(this.title),
                    (this.panel = this.theme.getIndentedPanel()),
                    this.container.appendChild(this.panel),
                    (this.title_controls = this.theme.getHeaderButtonHolder()),
                    this.title.appendChild(this.title_controls),
                    (this.controls = this.theme.getHeaderButtonHolder()),
                    this.title.appendChild(this.controls),
                    (this.row_holder = document.createElement('div')),
                    this.panel.appendChild(this.row_holder);
                else {
                  (this.header = document.createElement('label')), (this.header.textContent = this.getTitle());
                  var t = document.createElement('span');
                  t.classList.add('je-array-subheader'),
                    (t.innerText = '( loop )'),
                    this.header.appendChild(t),
                    (this.title = this.theme.getHeader(this.header, this.getPathDepth())),
                    this.container.appendChild(this.title),
                    this.options.infoText && ((this.infoButton = this.theme.getInfoButton(this.translateProperty(this.options.infoText))), this.container.appendChild(this.infoButton)),
                    (this.title_controls = this.theme.getHeaderButtonHolder()),
                    this.title.appendChild(this.title_controls),
                    this.schema.description && ((this.description = this.theme.getDescription(this.translateProperty(this.schema.description))), this.container.appendChild(this.description)),
                    (this.error_holder = document.createElement('div')),
                    this.container.appendChild(this.error_holder),
                    'tabs-top' === this.schema.format
                      ? ((this.controls = this.theme.getHeaderButtonHolder()),
                        this.title.appendChild(this.controls),
                        (this.tabs_holder = this.theme.getTopTabHolder(this.getValidId(this.getItemTitle()))),
                        this.container.appendChild(this.tabs_holder),
                        (this.row_holder = this.theme.getTopTabContentHolder(this.tabs_holder)),
                        (this.active_tab = null))
                      : 'tabs' === this.schema.format
                      ? ((this.controls = this.theme.getHeaderButtonHolder()),
                        this.title.appendChild(this.controls),
                        (this.tabs_holder = this.theme.getTabHolder(this.getValidId(this.getItemTitle()))),
                        this.container.appendChild(this.tabs_holder),
                        (this.row_holder = this.theme.getTabContentHolder(this.tabs_holder)),
                        (this.active_tab = null))
                      : ((this.panel = this.theme.getIndentedPanel()),
                        this.container.appendChild(this.panel),
                        (this.row_holder = document.createElement('div')),
                        this.panel.appendChild(this.row_holder),
                        (this.controls = this.theme.getButtonHolder()),
                        this.array_controls_top ? this.title.appendChild(this.controls) : this.panel.appendChild(this.controls));
                }
                this.addControls();
              },
            },
            {
              key: 'onChildEditorChange',
              value: function(t) {
                this.refreshValue(), this.refreshTabs(!0), z(W(o.prototype), 'onChildEditorChange', this).call(this, t);
              },
            },
            {
              key: 'getItemTitle',
              value: function() {
                if (!this.item_title)
                  if (this.schema.items && !Array.isArray(this.schema.items)) {
                    var t = this.jsoneditor.expandRefs(this.schema.items);
                    this.item_title = this.translateProperty(t.title) || this.translate('default_array_item_title');
                  } else this.item_title = this.translate('default_array_item_title');
                return this.cleanText(this.item_title);
              },
            },
            {
              key: 'getItemSchema',
              value: function(t) {
                return Array.isArray(this.schema.items)
                  ? t >= this.schema.items.length
                    ? !0 === this.schema.additionalItems
                      ? {}
                      : this.schema.additionalItems
                      ? f({}, this.schema.additionalItems)
                      : void 0
                    : f({}, this.schema.items[t])
                  : this.schema.items
                  ? f({}, this.schema.items)
                  : {};
              },
            },
            {
              key: 'getItemInfo',
              value: function(t) {
                var e = this.getItemSchema(t);
                this.item_info = this.item_info || {};
                var r = JSON.stringify(e);
                return (
                  void 0 !== this.item_info[r] ||
                    ((e = this.jsoneditor.expandRefs(e)),
                    (this.item_info[r] = {
                      title: this.translateProperty(e.title) || this.translate('default_array_item_title'),
                      default: e.default,
                      width: 12,
                      child_editors: e.properties || e.items,
                    })),
                  this.item_info[r]
                );
              },
            },
            {
              key: 'getElementEditor',
              value: function(t) {
                var e = this.getItemInfo(t),
                  r = this.getItemSchema(t);
                (r = this.jsoneditor.expandRefs(r)).title = ''.concat(e.title, ' ').concat(t + 1);
                var n,
                  i = this.jsoneditor.getEditorClass(r);
                this.tabs_holder
                  ? ((n = 'tabs-top' === this.schema.format ? this.theme.getTopTabContent() : this.theme.getTabContent()).id = ''.concat(this.path, '.').concat(t))
                  : (n = e.child_editors ? this.theme.getChildEditorHolder() : this.theme.getIndentedPanel()),
                  this.row_holder.appendChild(n);
                var o = this.jsoneditor.createEditor(i, {
                  jsoneditor: this.jsoneditor,
                  schema: r,
                  container: n,
                  path: ''.concat(this.path, '.').concat(t),
                  template_path: ''.concat(this.template_path, ':'),
                  parent: this,
                  required: !0,
                });
                return o.preBuild(), o.build(), o.postBuild(), o.title_controls || ((o.array_controls = this.theme.getButtonHolder()), n.appendChild(o.array_controls)), o;
              },
            },
            {
              key: 'checkParent',
              value: function(t) {
                return t && t.parentNode;
              },
            },
            {
              key: 'destroy',
              value: function() {
                this.empty(!0),
                  this.checkParent(this.title) && this.title.parentNode.removeChild(this.title),
                  this.checkParent(this.description) && this.description.parentNode.removeChild(this.description),
                  this.checkParent(this.row_holder) && this.row_holder.parentNode.removeChild(this.row_holder),
                  this.checkParent(this.controls) && this.controls.parentNode.removeChild(this.controls),
                  this.checkParent(this.panel) && this.panel.parentNode.removeChild(this.panel),
                  (this.rows = this.row_cache = this.title = this.description = this.row_holder = this.panel = this.controls = null),
                  z(W(o.prototype), 'destroy', this).call(this);
              },
            },
            {
              key: 'empty',
              value: function(t) {
                var e = this;
                this.rows &&
                  (this.rows.forEach(function(r, n) {
                    t && (e.checkParent(r.tab) && r.tab.parentNode.removeChild(r.tab), e.destroyRow(r, !0), (e.row_cache[n] = null)), (e.rows[n] = null);
                  }),
                  (this.rows = []),
                  t && (this.row_cache = []));
              },
            },
            {
              key: 'destroyRow',
              value: function(t, e) {
                var r = t.container;
                e
                  ? (t.destroy(), r.parentNode && r.parentNode.removeChild(r), this.checkParent(t.tab) && t.tab.parentNode.removeChild(t.tab))
                  : (t.tab && (t.tab.style.display = 'none'), (r.style.display = 'none'), t.unregister());
              },
            },
            {
              key: 'getMax',
              value: function() {
                return Array.isArray(this.schema.items) && !1 === this.schema.additionalItems ? Math.min(this.schema.items.length, this.schema.maxItems || 1 / 0) : this.schema.maxItems || 1 / 0;
              },
            },
            {
              key: 'refreshTabs',
              value: function(t) {
                var e = this;
                this.rows.forEach(function(r) {
                  r.tab && (t ? (r.tab_text.textContent = r.getHeaderText()) : r.tab === e.active_tab ? e.theme.markTabActive(r) : e.theme.markTabInactive(r));
                });
              },
            },
            {
              key: 'ensureArraySize',
              value: function(t) {
                if ((Array.isArray(t) || (t = [t]), this.schema.minItems)) for (; t.length < this.schema.minItems; ) t.push(this.getItemInfo(t.length).default);
                return this.getMax() && t.length > this.getMax() && (t = t.slice(0, this.getMax())), t;
              },
            },
            {
              key: 'setValue',
              value: function() {
                var t = this,
                  e = arguments.length > 0 && void 0 !== arguments[0] ? arguments[0] : [],
                  r = arguments.length > 1 ? arguments[1] : void 0;
                e = this.ensureArraySize(e);
                var n = JSON.stringify(e);
                if (n !== this.serialized) {
                  e.forEach(function(e, n) {
                    if (t.rows[n]) t.rows[n].setValue(e, r);
                    else if (t.row_cache[n])
                      (t.rows[n] = t.row_cache[n]),
                        t.rows[n].setValue(e, r),
                        (t.rows[n].container.style.display = ''),
                        t.rows[n].tab && (t.rows[n].tab.style.display = ''),
                        t.rows[n].register(),
                        t.jsoneditor.trigger('addRow', t.rows[n]);
                    else {
                      var i = t.addRow(e, r);
                      t.jsoneditor.trigger('addRow', i);
                    }
                  });
                  for (var i = e.length; i < this.rows.length; i++) this.destroyRow(this.rows[i]), (this.rows[i] = null);
                  this.rows = this.rows.slice(0, e.length);
                  var o = this.rows.find(function(e) {
                      return e.tab === t.active_tab;
                    }),
                    a = void 0 !== o ? o.tab : null;
                  !a && this.rows.length && (a = this.rows[0].tab), (this.active_tab = a), this.refreshValue(r), this.refreshTabs(!0), this.refreshTabs(), this.onChange();
                }
              },
            },
            {
              key: 'setVisibility',
              value: function(t, e) {
                t.style.display = e ? '' : 'none';
              },
            },
            {
              key: 'setupButtons',
              value: function(t) {
                var e = [];
                if (this.value.length)
                  if (1 === this.value.length) {
                    this.remove_all_rows_button.style.display = 'none';
                    var r = !(t || this.hide_delete_last_row_buttons);
                    this.setVisibility(this.delete_last_row_button, r), e.push(r);
                  } else {
                    var n = !(t || this.hide_delete_last_row_buttons);
                    this.setVisibility(this.delete_last_row_button, n), e.push(n);
                    var i = !(t || this.hide_delete_all_rows_buttons);
                    this.setVisibility(this.remove_all_rows_button, i), e.push(i);
                  }
                else (this.delete_last_row_button.style.display = 'none'), (this.remove_all_rows_button.style.display = 'none');
                var o = !((this.getMax() && this.getMax() <= this.rows.length) || this.hide_add_button);
                return (
                  this.setVisibility(this.add_row_button, o),
                  e.push(o),
                  e.some(function(t) {
                    return t;
                  })
                );
              },
            },
            {
              key: 'refreshValue',
              value: function(t) {
                var e = this,
                  r = this.value ? this.value.length : 0;
                if (
                  ((this.value = this.rows.map(function(t) {
                    return t.getValue();
                  })),
                  r !== this.value.length || t)
                ) {
                  var n = this.schema.minItems && this.schema.minItems >= this.rows.length;
                  this.rows.forEach(function(t, r) {
                    if (t.movedown_button) {
                      var i = r !== e.rows.length - 1;
                      e.setVisibility(t.movedown_button, i);
                    }
                    t.delete_button && e.setVisibility(t.delete_button, !n), (e.value[r] = t.getValue());
                  }),
                    !this.collapsed && this.setupButtons(n) ? (this.controls.style.display = 'inline-block') : (this.controls.style.display = 'none');
                }
                this.serialized = JSON.stringify(this.value);
              },
            },
            {
              key: 'addRow',
              value: function(t, e) {
                var r = this,
                  n = this.rows.length;
                (this.rows[n] = this.getElementEditor(n)),
                  (this.row_cache[n] = this.rows[n]),
                  this.tabs_holder &&
                    ((this.rows[n].tab_text = document.createElement('span')),
                    (this.rows[n].tab_text.textContent = this.rows[n].getHeaderText()),
                    'tabs-top' === this.schema.format
                      ? ((this.rows[n].tab = this.theme.getTopTab(this.rows[n].tab_text, this.getValidId(this.rows[n].path))), this.theme.addTopTab(this.tabs_holder, this.rows[n].tab))
                      : ((this.rows[n].tab = this.theme.getTab(this.rows[n].tab_text, this.getValidId(this.rows[n].path))), this.theme.addTab(this.tabs_holder, this.rows[n].tab)),
                    this.rows[n].tab.addEventListener('click', function(t) {
                      (r.active_tab = r.rows[n].tab), r.refreshTabs(), t.preventDefault(), t.stopPropagation();
                    }));
                var i = this.rows[n].title_controls || this.rows[n].array_controls;
                return (
                  this.hide_delete_buttons || (this.rows[n].delete_button = this._createDeleteButton(n, i)),
                  this.show_copy_button && (this.rows[n].copy_button = this._createCopyButton(n, i)),
                  n && !this.hide_move_buttons && (this.rows[n].moveup_button = this._createMoveUpButton(n, i)),
                  this.hide_move_buttons || (this.rows[n].movedown_button = this._createMoveDownButton(n, i)),
                  void 0 !== t && this.rows[n].setValue(t, e),
                  this.refreshTabs(),
                  this.rows[n]
                );
              },
            },
            {
              key: '_createDeleteButton',
              value: function(t, e) {
                var r = this,
                  n = this.getButton(this.getItemTitle(), 'delete', 'button_delete_row_title', [this.getItemTitle()]);
                return (
                  n.classList.add('delete', 'json-editor-btntype-delete'),
                  n.setAttribute('data-i', t),
                  n.addEventListener('click', function(t) {
                    if ((t.preventDefault(), t.stopPropagation(), !r.askConfirmation())) return !1;
                    var e = 1 * t.currentTarget.getAttribute('data-i'),
                      n = r.getValue().filter(function(t, r) {
                        return r !== e;
                      }),
                      i = null,
                      o = r.rows[e];
                    r.setValue(n),
                      r.rows[e] ? (i = r.rows[e].tab) : r.rows[e - 1] && (i = r.rows[e - 1].tab),
                      i && ((r.active_tab = i), r.refreshTabs()),
                      r.onChange(!0),
                      r.jsoneditor.trigger('deleteRow', o);
                  }),
                  e && e.appendChild(n),
                  n
                );
              },
            },
            {
              key: '_createCopyButton',
              value: function(t, e) {
                var r = this,
                  n = this.getButton(this.getItemTitle(), 'copy', 'button_copy_row_title', [this.getItemTitle()]);
                return (
                  n.classList.add('copy', 'json-editor-btntype-copy'),
                  n.setAttribute('data-i', t),
                  n.addEventListener('click', function(t) {
                    var e = r.getValue();
                    t.preventDefault(), t.stopPropagation();
                    var n = 1 * t.currentTarget.getAttribute('data-i');
                    e.forEach(function(t, r) {
                      r === n && e.push(t);
                    }),
                      r.setValue(e),
                      r.refreshValue(!0),
                      r.onChange(!0);
                  }),
                  e.appendChild(n),
                  n
                );
              },
            },
            {
              key: '_createMoveUpButton',
              value: function(t, e) {
                var r = this,
                  n = this.getButton('', 'tabs-top' === this.schema.format ? 'moveleft' : 'moveup', 'button_move_up_title');
                return (
                  n.classList.add('moveup', 'json-editor-btntype-move'),
                  n.setAttribute('data-i', t),
                  n.addEventListener('click', function(t) {
                    t.preventDefault(), t.stopPropagation();
                    var e = 1 * t.currentTarget.getAttribute('data-i');
                    if (!(e <= 0)) {
                      var n = r.getValue(),
                        i = n[e - 1];
                      (n[e - 1] = n[e]), (n[e] = i), r.setValue(n), (r.active_tab = r.rows[e - 1].tab), r.refreshTabs(), r.onChange(!0), r.jsoneditor.trigger('moveRow', r.rows[e - 1]);
                    }
                  }),
                  e && e.appendChild(n),
                  n
                );
              },
            },
            {
              key: '_createMoveDownButton',
              value: function(t, e) {
                var r = this,
                  n = this.getButton('', 'tabs-top' === this.schema.format ? 'moveright' : 'movedown', 'button_move_down_title');
                return (
                  n.classList.add('movedown', 'json-editor-btntype-move'),
                  n.setAttribute('data-i', t),
                  n.addEventListener('click', function(t) {
                    t.preventDefault(), t.stopPropagation();
                    var e = 1 * t.currentTarget.getAttribute('data-i'),
                      n = r.getValue();
                    if (!(e >= n.length - 1)) {
                      var i = n[e + 1];
                      (n[e + 1] = n[e]), (n[e] = i), r.setValue(n), (r.active_tab = r.rows[e + 1].tab), r.refreshTabs(), r.onChange(!0), r.jsoneditor.trigger('moveRow', r.rows[e + 1]);
                    }
                  }),
                  e && e.appendChild(n),
                  n
                );
              },
            },
            {
              key: 'addControls',
              value: function() {
                (this.collapsed = !1),
                  (this.toggle_button = this._createToggleButton()),
                  this.options.collapsed && y(this.toggle_button, 'click'),
                  this.schema.options && void 0 !== this.schema.options.disable_collapse
                    ? this.schema.options.disable_collapse && (this.toggle_button.style.display = 'none')
                    : this.jsoneditor.options.disable_collapse && (this.toggle_button.style.display = 'none'),
                  (this.add_row_button = this._createAddRowButton()),
                  (this.delete_last_row_button = this._createDeleteLastRowButton()),
                  (this.remove_all_rows_button = this._createRemoveAllRowsButton()),
                  this.tabs &&
                    (this.add_row_button.classList.add('je-array-control-btn'),
                    this.delete_last_row_button.classList.add('je-array-control-btn'),
                    this.remove_all_rows_button.classList.add('je-array-control-btn'));
              },
            },
            {
              key: '_createToggleButton',
              value: function() {
                var t = this,
                  e = this.getButton('', 'collapse', 'button_collapse');
                e.classList.add('json-editor-btntype-toggle'), this.title.insertBefore(e, this.title.childNodes[0]);
                var r = this.row_holder.style.display,
                  n = this.controls.style.display;
                return (
                  e.addEventListener('click', function(e) {
                    e.preventDefault(),
                      e.stopPropagation(),
                      t.panel && t.setVisibility(t.panel, t.collapsed),
                      t.tabs_holder && t.setVisibility(t.tabs_holder, t.collapsed),
                      t.collapsed
                        ? ((t.collapsed = !1), (t.row_holder.style.display = r), (t.controls.style.display = n), t.setButtonText(e.currentTarget, '', 'collapse', 'button_collapse'))
                        : ((t.collapsed = !0), (t.row_holder.style.display = 'none'), (t.controls.style.display = 'none'), t.setButtonText(e.currentTarget, '', 'expand', 'button_expand'));
                  }),
                  e
                );
              },
            },
            {
              key: '_createAddRowButton',
              value: function() {
                var t = this,
                  e = this.getButton(this.getItemTitle(), 'add', 'button_add_row_title', [this.getItemTitle()]);
                return (
                  e.classList.add('json-editor-btntype-add'),
                  e.addEventListener('click', function(e) {
                    e.preventDefault(), e.stopPropagation();
                    var r,
                      n = t.rows.length;
                    t.row_cache[n]
                      ? ((r = t.rows[n] = t.row_cache[n]),
                        t.rows[n].setValue(t.rows[n].getDefault(), !0),
                        (t.rows[n].container.style.display = ''),
                        t.rows[n].tab && (t.rows[n].tab.style.display = ''),
                        t.rows[n].register())
                      : (r = t.addRow()),
                      (t.active_tab = t.rows[n].tab),
                      t.refreshTabs(),
                      t.refreshValue(),
                      t.onChange(!0),
                      t.jsoneditor.trigger('addRow', r);
                  }),
                  this.controls.appendChild(e),
                  e
                );
              },
            },
            {
              key: '_createDeleteLastRowButton',
              value: function() {
                var t = this,
                  e = this.getButton('button_delete_last', 'subtract', 'button_delete_last_title', [this.getItemTitle()]);
                return (
                  e.classList.add('json-editor-btntype-deletelast'),
                  e.addEventListener('click', function(e) {
                    if ((e.preventDefault(), e.stopPropagation(), !t.askConfirmation())) return !1;
                    var r = t.getValue(),
                      n = null,
                      i = r.pop();
                    t.setValue(r), t.rows[t.rows.length - 1] && (n = t.rows[t.rows.length - 1].tab), n && ((t.active_tab = n), t.refreshTabs()), t.onChange(!0), t.jsoneditor.trigger('deleteRow', i);
                  }),
                  this.controls.appendChild(e),
                  e
                );
              },
            },
            {
              key: '_createRemoveAllRowsButton',
              value: function() {
                var t = this,
                  e = this.getButton('button_delete_all', 'delete', 'button_delete_all_title');
                return (
                  e.classList.add('json-editor-btntype-deleteall'),
                  e.addEventListener('click', function(e) {
                    if ((e.preventDefault(), e.stopPropagation(), !t.askConfirmation())) return !1;
                    t.empty(!0), t.setValue([]), t.onChange(!0), t.jsoneditor.trigger('deleteAllRows');
                  }),
                  this.controls.appendChild(e),
                  e
                );
              },
            },
            {
              key: 'showValidationErrors',
              value: function(t) {
                var e = this,
                  r = [],
                  n = [];
                t.forEach(function(t) {
                  t.path === e.path ? r.push(t) : n.push(t);
                }),
                  this.error_holder &&
                    (r.length
                      ? ((this.error_holder.innerHTML = ''),
                        (this.error_holder.style.display = ''),
                        r.forEach(function(t) {
                          e.error_holder.appendChild(e.theme.getErrorMessage(t.message));
                        }))
                      : (this.error_holder.style.display = 'none')),
                  this.rows.forEach(function(t) {
                    return t.showValidationErrors(n);
                  });
              },
            },
          ]) && U(e.prototype, r),
          n && U(e, n),
          o
        );
      })(M);
      function X(t) {
        return (X =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function K(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      function Z(t, e, r) {
        return (Z =
          'undefined' != typeof Reflect && Reflect.get
            ? Reflect.get
            : function(t, e, r) {
                var n = (function(t, e) {
                  for (; !Object.prototype.hasOwnProperty.call(t, e) && null !== (t = rt(t)); );
                  return t;
                })(t, e);
                if (n) {
                  var i = Object.getOwnPropertyDescriptor(n, e);
                  return i.get ? i.get.call(r) : i.value;
                }
              })(t, e, r || t);
      }
      function Q(t, e) {
        return (Q =
          Object.setPrototypeOf ||
          function(t, e) {
            return (t.__proto__ = e), t;
          })(t, e);
      }
      function tt(t) {
        var e = (function() {
          if ('undefined' == typeof Reflect || !Reflect.construct) return !1;
          if (Reflect.construct.sham) return !1;
          if ('function' == typeof Proxy) return !0;
          try {
            return Boolean.prototype.valueOf.call(Reflect.construct(Boolean, [], function() {})), !0;
          } catch (t) {
            return !1;
          }
        })();
        return function() {
          var r,
            n = rt(t);
          if (e) {
            var i = rt(this).constructor;
            r = Reflect.construct(n, arguments, i);
          } else r = n.apply(this, arguments);
          return et(this, r);
        };
      }
      function et(t, e) {
        return !e || ('object' !== X(e) && 'function' != typeof e)
          ? (function(t) {
              if (void 0 === t) throw new ReferenceError("this hasn't been initialised - super() hasn't been called");
              return t;
            })(t)
          : e;
      }
      function rt(t) {
        return (rt = Object.setPrototypeOf
          ? Object.getPrototypeOf
          : function(t) {
              return t.__proto__ || Object.getPrototypeOf(t);
            })(t);
      }
      Y.rules = { '.json-editor-btntype-toggle': 'margin:0%2010px%200%200', '.je-array-control-btn': 'width:100%25;text-align:left;margin-bottom:3px' };
      var nt = (function(t) {
        !(function(t, e) {
          if ('function' != typeof e && null !== e) throw new TypeError('Super expression must either be null or a function');
          (t.prototype = Object.create(e && e.prototype, { constructor: { value: t, writable: !0, configurable: !0 } })), e && Q(t, e);
        })(o, t);
        var e,
          r,
          n,
          i = tt(o);
        function o(t, e) {
          var r;
          return (
            (function(t, e) {
              if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
            })(this, o),
            ((r = i.call(this, t, e)).active = !1),
            r.parent &&
              r.parent.schema &&
              (Array.isArray(r.parent.schema.required) ? r.parent.schema.required.includes(r.key) || r.parent.schema.required.push(r.key) : (r.parent.schema.required = [r.key])),
            r
          );
        }
        return (
          (e = o),
          (r = [
            {
              key: 'build',
              value: function() {
                var t = this;
                this.options.compact = !0;
                var e = this.translateProperty(this.schema.title) || this.key,
                  r = this.expandCallbacks(
                    'button',
                    f(
                      {},
                      {
                        icon: '',
                        validated: !1,
                        align: 'left',
                        action: function(t, e) {
                          window.alert('No button action defined for "'.concat(t.path, '"'));
                        },
                      },
                      this.defaults.options.button || {},
                      this.options.button || {}
                    )
                  );
                (this.input = this.theme.getFormButton(e, r.icon, e)),
                  this.input.addEventListener('click', r.action, !1),
                  (this.schema.readOnly || this.schema.readonly || this.schema.template) && (this.disable(!0), this.input.setAttribute('readonly', 'true')),
                  this.setInputAttributes(['readonly']),
                  (this.control = this.theme.getFormButtonHolder(r.align)),
                  this.control.appendChild(this.input),
                  this.container.appendChild(this.control),
                  (this.changeHandler = function() {
                    t.jsoneditor.validate(t.jsoneditor.getValue()).length > 0 ? t.disable() : t.enable();
                  }),
                  r.validated && this.jsoneditor.on('change', this.changeHandler);
              },
            },
            {
              key: 'enable',
              value: function() {
                this.always_disabled || ((this.input.disabled = !1), Z(rt(o.prototype), 'enable', this).call(this));
              },
            },
            {
              key: 'disable',
              value: function(t) {
                t && (this.always_disabled = !0), (this.input.disabled = !0), Z(rt(o.prototype), 'disable', this).call(this);
              },
            },
            {
              key: 'getNumColumns',
              value: function() {
                return 2;
              },
            },
            {
              key: 'activate',
              value: function() {
                (this.active = !1), this.enable();
              },
            },
            {
              key: 'deactivate',
              value: function() {
                this.isRequired() || ((this.active = !1), this.disable());
              },
            },
            {
              key: 'destroy',
              value: function() {
                this.jsoneditor.off('change', this.changeHandler), (this.changeHandler = null), Z(rt(o.prototype), 'destroy', this).call(this);
              },
            },
          ]) && K(e.prototype, r),
          n && K(e, n),
          o
        );
      })(M);
      function it(t) {
        return (it =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function ot(t, e) {
        if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
      }
      function at(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      function st(t, e, r) {
        return (st =
          'undefined' != typeof Reflect && Reflect.get
            ? Reflect.get
            : function(t, e, r) {
                var n = (function(t, e) {
                  for (; !Object.prototype.hasOwnProperty.call(t, e) && null !== (t = ht(t)); );
                  return t;
                })(t, e);
                if (n) {
                  var i = Object.getOwnPropertyDescriptor(n, e);
                  return i.get ? i.get.call(r) : i.value;
                }
              })(t, e, r || t);
      }
      function lt(t, e) {
        return (lt =
          Object.setPrototypeOf ||
          function(t, e) {
            return (t.__proto__ = e), t;
          })(t, e);
      }
      function ct(t) {
        var e = (function() {
          if ('undefined' == typeof Reflect || !Reflect.construct) return !1;
          if (Reflect.construct.sham) return !1;
          if ('function' == typeof Proxy) return !0;
          try {
            return Boolean.prototype.valueOf.call(Reflect.construct(Boolean, [], function() {})), !0;
          } catch (t) {
            return !1;
          }
        })();
        return function() {
          var r,
            n = ht(t);
          if (e) {
            var i = ht(this).constructor;
            r = Reflect.construct(n, arguments, i);
          } else r = n.apply(this, arguments);
          return ut(this, r);
        };
      }
      function ut(t, e) {
        return !e || ('object' !== it(e) && 'function' != typeof e)
          ? (function(t) {
              if (void 0 === t) throw new ReferenceError("this hasn't been initialised - super() hasn't been called");
              return t;
            })(t)
          : e;
      }
      function ht(t) {
        return (ht = Object.setPrototypeOf
          ? Object.getPrototypeOf
          : function(t) {
              return t.__proto__ || Object.getPrototypeOf(t);
            })(t);
      }
      var dt = (function(t) {
        !(function(t, e) {
          if ('function' != typeof e && null !== e) throw new TypeError('Super expression must either be null or a function');
          (t.prototype = Object.create(e && e.prototype, { constructor: { value: t, writable: !0, configurable: !0 } })), e && lt(t, e);
        })(o, t);
        var e,
          r,
          n,
          i = ct(o);
        function o() {
          return ot(this, o), i.apply(this, arguments);
        }
        return (
          (e = o),
          (r = [
            {
              key: 'setValue',
              value: function(t, e) {
                t = !!t;
                var r = this.getValue() !== t;
                (this.value = t), (this.input.checked = this.value), this.onChange(r);
              },
            },
            {
              key: 'register',
              value: function() {
                st(ht(o.prototype), 'register', this).call(this), this.input && this.input.setAttribute('name', this.formname);
              },
            },
            {
              key: 'unregister',
              value: function() {
                st(ht(o.prototype), 'unregister', this).call(this), this.input && this.input.removeAttribute('name');
              },
            },
            {
              key: 'getNumColumns',
              value: function() {
                return Math.min(12, Math.max(this.getTitle().length / 7, 2));
              },
            },
            {
              key: 'build',
              value: function() {
                var t = this;
                this.parent.options.table_row || ((this.label = this.header = this.theme.getCheckboxLabel(this.getTitle(), this.isRequired())), (this.label.htmlFor = this.formname)),
                  this.schema.description && (this.description = this.theme.getFormInputDescription(this.translateProperty(this.schema.description))),
                  this.options.infoText && !this.options.compact && (this.infoButton = this.theme.getInfoButton(this.translateProperty(this.options.infoText))),
                  this.options.compact && this.container.classList.add('compact'),
                  (this.input = this.theme.getCheckbox()),
                  (this.input.id = this.formname),
                  (this.control = this.theme.getFormControl(this.label, this.input, this.description, this.infoButton)),
                  (this.schema.readOnly || this.schema.readonly) && (this.disable(!0), (this.input.disabled = !0)),
                  this.input.addEventListener('change', function(e) {
                    e.preventDefault(), e.stopPropagation(), (t.value = e.currentTarget.checked), t.onChange(!0);
                  }),
                  this.container.appendChild(this.control);
              },
            },
            {
              key: 'enable',
              value: function() {
                this.always_disabled || ((this.input.disabled = !1), st(ht(o.prototype), 'enable', this).call(this));
              },
            },
            {
              key: 'disable',
              value: function(t) {
                t && (this.always_disabled = !0), (this.input.disabled = !0), st(ht(o.prototype), 'disable', this).call(this);
              },
            },
            {
              key: 'destroy',
              value: function() {
                this.label && this.label.parentNode && this.label.parentNode.removeChild(this.label),
                  this.description && this.description.parentNode && this.description.parentNode.removeChild(this.description),
                  this.input && this.input.parentNode && this.input.parentNode.removeChild(this.input),
                  st(ht(o.prototype), 'destroy', this).call(this);
              },
            },
            {
              key: 'showValidationErrors',
              value: function(t) {
                var e = this;
                this.previous_error_setting = this.jsoneditor.options.show_errors;
                var r = t.reduce(function(t, r) {
                  return r.path === e.path && t.push(r.message), t;
                }, []);
                (this.input.controlgroup = this.control), r.length ? this.theme.addInputError(this.input, ''.concat(r.join('. '), '.')) : this.theme.removeInputError(this.input);
              },
            },
          ]) && at(e.prototype, r),
          n && at(e, n),
          o
        );
      })(M);
      function pt(t) {
        return (pt =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function ft(t, e) {
        if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
      }
      function yt(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      function mt(t, e, r) {
        return (mt =
          'undefined' != typeof Reflect && Reflect.get
            ? Reflect.get
            : function(t, e, r) {
                var n = (function(t, e) {
                  for (; !Object.prototype.hasOwnProperty.call(t, e) && null !== (t = _t(t)); );
                  return t;
                })(t, e);
                if (n) {
                  var i = Object.getOwnPropertyDescriptor(n, e);
                  return i.get ? i.get.call(r) : i.value;
                }
              })(t, e, r || t);
      }
      function vt(t, e) {
        return (vt =
          Object.setPrototypeOf ||
          function(t, e) {
            return (t.__proto__ = e), t;
          })(t, e);
      }
      function bt(t) {
        var e = (function() {
          if ('undefined' == typeof Reflect || !Reflect.construct) return !1;
          if (Reflect.construct.sham) return !1;
          if ('function' == typeof Proxy) return !0;
          try {
            return Boolean.prototype.valueOf.call(Reflect.construct(Boolean, [], function() {})), !0;
          } catch (t) {
            return !1;
          }
        })();
        return function() {
          var r,
            n = _t(t);
          if (e) {
            var i = _t(this).constructor;
            r = Reflect.construct(n, arguments, i);
          } else r = n.apply(this, arguments);
          return gt(this, r);
        };
      }
      function gt(t, e) {
        return !e || ('object' !== pt(e) && 'function' != typeof e)
          ? (function(t) {
              if (void 0 === t) throw new ReferenceError("this hasn't been initialised - super() hasn't been called");
              return t;
            })(t)
          : e;
      }
      function _t(t) {
        return (_t = Object.setPrototypeOf
          ? Object.getPrototypeOf
          : function(t) {
              return t.__proto__ || Object.getPrototypeOf(t);
            })(t);
      }
      var wt = (function(t) {
        !(function(t, e) {
          if ('function' != typeof e && null !== e) throw new TypeError('Super expression must either be null or a function');
          (t.prototype = Object.create(e && e.prototype, { constructor: { value: t, writable: !0, configurable: !0 } })), e && vt(t, e);
        })(o, t);
        var e,
          r,
          n,
          i = bt(o);
        function o() {
          return ft(this, o), i.apply(this, arguments);
        }
        return (
          (e = o),
          (r = [
            {
              key: 'register',
              value: function() {
                mt(_t(o.prototype), 'register', this).call(this), this.input && this.input.setAttribute('name', this.formname);
              },
            },
            {
              key: 'unregister',
              value: function() {
                mt(_t(o.prototype), 'unregister', this).call(this), this.input && this.input.removeAttribute('name');
              },
            },
            {
              key: 'setValue',
              value: function(t, e, r) {
                if ((!this.template || r) && (null == t ? (t = '') : 'object' === pt(t) ? (t = JSON.stringify(t)) : 'string' != typeof t && (t = ''.concat(t)), t !== this.serialized)) {
                  var n = this.sanitize(t);
                  if (this.input.value !== n) {
                    this.input.value = n;
                    var i = r || this.getValue() !== t;
                    this.refreshValue(),
                      e ? (this.is_dirty = !1) : 'change' === this.jsoneditor.options.show_errors && (this.is_dirty = !0),
                      this.adjust_height && this.adjust_height(this.input),
                      this.onChange(i);
                  }
                }
              },
            },
            {
              key: 'getNumColumns',
              value: function() {
                return 2;
              },
            },
            {
              key: 'enable',
              value: function() {
                mt(_t(o.prototype), 'enable', this).call(this);
              },
            },
            {
              key: 'disable',
              value: function() {
                mt(_t(o.prototype), 'disable', this).call(this);
              },
            },
            {
              key: 'refreshValue',
              value: function() {
                (this.value = this.input.value), 'string' != typeof this.value && (this.value = ''), (this.serialized = this.value);
              },
            },
            {
              key: 'destroy',
              value: function() {
                (this.template = null),
                  this.input && this.input.parentNode && this.input.parentNode.removeChild(this.input),
                  this.label && this.label.parentNode && this.label.parentNode.removeChild(this.label),
                  this.description && this.description.parentNode && this.description.parentNode.removeChild(this.description),
                  mt(_t(o.prototype), 'destroy', this).call(this);
              },
            },
            {
              key: 'sanitize',
              value: function(t) {
                return t;
              },
            },
            {
              key: 'onWatchedFieldChange',
              value: function() {
                var t;
                this.template && ((t = this.getWatchedFieldValues()), this.setValue(this.template(t), !1, !0)), mt(_t(o.prototype), 'onWatchedFieldChange', this).call(this);
              },
            },
            {
              key: 'build',
              value: function() {
                if (
                  ((this.format = this.schema.format),
                  !this.format && this.options.default_format && (this.format = this.options.default_format),
                  this.options.format && (this.format = this.options.format),
                  (this.input_type = 'hidden'),
                  (this.input = this.theme.getFormInputField(this.input_type)),
                  this.format && this.input.setAttribute('data-schemaformat', this.format),
                  this.container.appendChild(this.input),
                  this.schema.template)
                ) {
                  var t = this.expandCallbacks('template', { template: this.schema.template });
                  'function' == typeof t.template ? (this.template = t.template) : (this.template = this.jsoneditor.compileTemplate(this.schema.template, this.template_engine)), this.refreshValue();
                } else this.refreshValue();
              },
            },
          ]) && yt(e.prototype, r),
          n && yt(e, n),
          o
        );
      })(M);
      function kt(t) {
        return (kt =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function xt(t, e) {
        if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
      }
      function jt(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      function Ot(t, e, r) {
        return (Ot =
          'undefined' != typeof Reflect && Reflect.get
            ? Reflect.get
            : function(t, e, r) {
                var n = (function(t, e) {
                  for (; !Object.prototype.hasOwnProperty.call(t, e) && null !== (t = At(t)); );
                  return t;
                })(t, e);
                if (n) {
                  var i = Object.getOwnPropertyDescriptor(n, e);
                  return i.get ? i.get.call(r) : i.value;
                }
              })(t, e, r || t);
      }
      function Et(t, e) {
        return (Et =
          Object.setPrototypeOf ||
          function(t, e) {
            return (t.__proto__ = e), t;
          })(t, e);
      }
      function Ct(t) {
        var e = (function() {
          if ('undefined' == typeof Reflect || !Reflect.construct) return !1;
          if (Reflect.construct.sham) return !1;
          if ('function' == typeof Proxy) return !0;
          try {
            return Boolean.prototype.valueOf.call(Reflect.construct(Boolean, [], function() {})), !0;
          } catch (t) {
            return !1;
          }
        })();
        return function() {
          var r,
            n = At(t);
          if (e) {
            var i = At(this).constructor;
            r = Reflect.construct(n, arguments, i);
          } else r = n.apply(this, arguments);
          return St(this, r);
        };
      }
      function St(t, e) {
        return !e || ('object' !== kt(e) && 'function' != typeof e)
          ? (function(t) {
              if (void 0 === t) throw new ReferenceError("this hasn't been initialised - super() hasn't been called");
              return t;
            })(t)
          : e;
      }
      function At(t) {
        return (At = Object.setPrototypeOf
          ? Object.getPrototypeOf
          : function(t) {
              return t.__proto__ || Object.getPrototypeOf(t);
            })(t);
      }
      var Pt = (function(t) {
        !(function(t, e) {
          if ('function' != typeof e && null !== e) throw new TypeError('Super expression must either be null or a function');
          (t.prototype = Object.create(e && e.prototype, { constructor: { value: t, writable: !0, configurable: !0 } })), e && Et(t, e);
        })(o, t);
        var e,
          r,
          n,
          i = Ct(o);
        function o() {
          return xt(this, o), i.apply(this, arguments);
        }
        return (
          (e = o),
          (r = [
            {
              key: 'register',
              value: function() {
                Ot(At(o.prototype), 'register', this).call(this), this.input && (this.input.setAttribute('name', this.formname), this.input.setAttribute('aria-label', this.formname));
              },
            },
            {
              key: 'unregister',
              value: function() {
                Ot(At(o.prototype), 'unregister', this).call(this), this.input && (this.input.removeAttribute('name'), this.input.removeAttribute('aria-label'));
              },
            },
            {
              key: 'setValue',
              value: function(t, e, r) {
                if (
                  (!this.template || r) &&
                  (this.shouldBeUnset() || null != t ? ('object' === kt(t) ? (t = JSON.stringify(t)) : this.shouldBeUnset() || 'string' == typeof t || (t = ''.concat(t))) : (t = ''),
                  t !== this.serialized)
                ) {
                  var n = this.sanitize(t);
                  if (this.input.value !== n) {
                    if ((this.setValueToInputField(n), 'range' === this.format)) {
                      var i = this.control.querySelector('output');
                      i && (i.value = n);
                    }
                    var o = r || this.getValue() !== t;
                    return (
                      this.refreshValue(),
                      e ? (this.is_dirty = !1) : 'change' === this.jsoneditor.options.show_errors && (this.is_dirty = !0),
                      this.adjust_height && this.adjust_height(this.input),
                      this.onChange(o),
                      { changed: o, value: n }
                    );
                  }
                }
              },
            },
            {
              key: 'setValueToInputField',
              value: function(t) {
                this.input.value = void 0 === t ? '' : t;
              },
            },
            {
              key: 'getNumColumns',
              value: function() {
                var t,
                  e = Math.ceil(Math.max(this.getTitle().length, this.schema.maxLength || 0, this.schema.minLength || 0) / 5);
                return (t = 'textarea' === this.input_type ? 6 : ['text', 'email'].includes(this.input_type) ? 4 : 2), Math.min(12, Math.max(e, t));
              },
            },
            {
              key: 'build',
              value: function() {
                var t = this;
                if (
                  (this.options.compact || (this.header = this.label = this.theme.getFormInputLabel(this.getTitle(), this.isRequired())),
                  this.schema.description && (this.description = this.theme.getFormInputDescription(this.translateProperty(this.schema.description))),
                  this.options.infoText && (this.infoButton = this.theme.getInfoButton(this.translateProperty(this.options.infoText))),
                  (this.format = this.schema.format),
                  !this.format && this.schema.media && this.schema.media.type && (this.format = this.schema.media.type.replace(/(^(application|text)\/(x-)?(script\.)?)|(-source$)/g, '')),
                  !this.format && this.options.default_format && (this.format = this.options.default_format),
                  this.options.format && (this.format = this.options.format),
                  this.format)
                )
                  if ('textarea' === this.format)
                    (this.input_type = 'textarea'),
                      (this.input_textarea_container = document.createElement('div')),
                      this.input_textarea_container.classList.add('je-textarea-container'),
                      (this.input = this.theme.getTextareaInput()),
                      (this.collapsed = !0),
                      (this.collapse_button = this.getButton('', 'expandinput', 'button_expand')),
                      this.collapse_button.setAttribute('tabIndex', '-1'),
                      this.input_textarea_container.appendChild(this.input),
                      this.input_textarea_container.appendChild(this.collapse_button),
                      this.collapse_button.addEventListener('mousedown', function(e) {
                        e.preventDefault(),
                          e.stopPropagation(),
                          t.collapsed
                            ? ((t.collapsed = !1), t.setButtonText(t.collapse_button, '', 'collapseinput', 'button_collapse'), t.input.classList.add('expanded'))
                            : ((t.collapsed = !0), t.setButtonText(t.collapse_button, '', 'expandinput', 'button_expand'), t.input.classList.remove('expanded'));
                      });
                  else if ('range' === this.format) {
                    this.input_type = 'range';
                    var e = this.schema.minimum || 0,
                      r = this.schema.maximum || Math.max(100, e + 1),
                      n = 1;
                    this.schema.multipleOf &&
                      (e % this.schema.multipleOf && (e = Math.ceil(e / this.schema.multipleOf) * this.schema.multipleOf),
                      r % this.schema.multipleOf && (r = Math.floor(r / this.schema.multipleOf) * this.schema.multipleOf),
                      (n = this.schema.multipleOf)),
                      (this.input = this.theme.getRangeInput(e, r, n));
                  } else
                    (this.input_type = 'text'),
                      [
                        'button',
                        'checkbox',
                        'color',
                        'date',
                        'datetime-local',
                        'email',
                        'file',
                        'hidden',
                        'image',
                        'month',
                        'number',
                        'password',
                        'radio',
                        'reset',
                        'search',
                        'submit',
                        'tel',
                        'text',
                        'time',
                        'url',
                        'week',
                      ].includes(this.format) && (this.input_type = this.format),
                      (this.input = this.theme.getFormInputField(this.input_type));
                else (this.input_type = 'text'), (this.input = this.theme.getFormInputField(this.input_type));
                void 0 !== this.schema.maxLength && this.input.setAttribute('maxlength', this.schema.maxLength),
                  void 0 !== this.schema.pattern
                    ? this.input.setAttribute('pattern', this.schema.pattern)
                    : void 0 !== this.schema.minLength && this.input.setAttribute('pattern', '.{'.concat(this.schema.minLength, ',}')),
                  this.options.compact ? this.container.classList.add('compact') : this.options.input_width && (this.input.style.width = this.options.input_width),
                  (this.schema.readOnly || this.schema.readonly || this.schema.template) && (this.disable(!0), this.input.setAttribute('readonly', 'true')),
                  this.setInputAttributes(['maxlength', 'pattern', 'readonly', 'min', 'max', 'step']),
                  this.input.addEventListener('change', function(e) {
                    if ((e.preventDefault(), e.stopPropagation(), t.schema.template)) e.currentTarget.value = t.value;
                    else {
                      var r = e.currentTarget.value,
                        n = t.sanitize(r);
                      r !== n && (e.currentTarget.value = n), (t.is_dirty = !0), t.refreshValue(), t.onChange(!0);
                    }
                  }),
                  this.options.input_height && (this.input.style.height = this.options.input_height),
                  this.options.expand_height &&
                    ((this.adjust_height = function(t) {
                      if (t) {
                        var e,
                          r = t.offsetHeight;
                        if (t.offsetHeight < t.scrollHeight) for (e = 0; t.offsetHeight < t.scrollHeight + 3 && !(e > 100); ) e++, r++, (t.style.height = ''.concat(r, 'px'));
                        else {
                          for (e = 0; t.offsetHeight >= t.scrollHeight + 3 && !(e > 100); ) e++, r--, (t.style.height = ''.concat(r, 'px'));
                          t.style.height = ''.concat(r + 1, 'px');
                        }
                      }
                    }),
                    this.input.addEventListener('keyup', function(e) {
                      t.adjust_height(e.currentTarget);
                    }),
                    this.input.addEventListener('change', function(e) {
                      t.adjust_height(e.currentTarget);
                    }),
                    this.adjust_height()),
                  this.format && this.input.setAttribute('data-schemaformat', this.format);
                var i = this.input;
                if (
                  ('range' === this.format && (i = this.theme.getRangeControl(this.input, this.theme.getRangeOutput(this.input, this.schema.default || Math.max(this.schema.minimum || 0, 0)))),
                  this.input_textarea_container && (i = this.input_textarea_container),
                  (this.control = this.theme.getFormControl(this.label, i, this.description, this.infoButton, this.formname)),
                  this.container.appendChild(this.control),
                  window.requestAnimationFrame(function() {
                    t.input.parentNode && t.afterInputReady(), t.adjust_height && t.adjust_height(t.input);
                  }),
                  this.schema.template)
                ) {
                  var o = this.expandCallbacks('template', { template: this.schema.template });
                  'function' == typeof o.template ? (this.template = o.template) : (this.template = this.jsoneditor.compileTemplate(this.schema.template, this.template_engine)), this.refreshValue();
                } else this.refreshValue();
              },
            },
            {
              key: 'setupCleave',
              value: function(t) {
                var e = this.expandCallbacks('cleave', f({}, this.defaults.options.cleave || {}, this.options.cleave || {}));
                'object' === kt(e) && Object.keys(e).length > 0 && (this.cleave_instance = new window.Cleave(t, e));
              },
            },
            {
              key: 'setupImask',
              value: function(t) {
                var e = this.expandCallbacks('imask', f({}, this.defaults.options.imask || {}, this.options.imask || {}));
                'object' === kt(e) && Object.keys(e).length > 0 && (this.imask_instance = window.IMask(t, this.ajustIMaskOptions(e)));
              },
            },
            {
              key: 'ajustIMaskOptions',
              value: function(t) {
                var e = this;
                return (
                  Object.keys(t).forEach(function(r) {
                    if (t[r] === Object(t[r])) t[r] = e.ajustIMaskOptions(t[r]);
                    else if ('mask' === r)
                      if ('regex:' === t[r].substr(0, 6)) {
                        var n = t[r].match(/^regex:\/(.*)\/([gimsuy]*)$/);
                        if (null !== n)
                          try {
                            t[r] = new RegExp(n[1], n[2]);
                          } catch (t) {}
                      } else t[r] = e.getGlobalPropertyFromString(t[r]);
                  }),
                  t
                );
              },
            },
            {
              key: 'getGlobalPropertyFromString',
              value: function(t) {
                if (t.includes('.')) {
                  var e = t.split('.'),
                    r = e[0],
                    n = e[1];
                  if (void 0 !== window[r] && void 0 !== window[r][n]) return window[r][n];
                } else if (void 0 !== window[t]) return window[t];
                return t;
              },
            },
            {
              key: 'shouldBeUnset',
              value: function() {
                return !this.jsoneditor.options.use_default_values && !this.is_dirty;
              },
            },
            {
              key: 'getValue',
              value: function() {
                var t = !(!this.input || !this.input.value);
                if (!this.shouldBeUnset() || t)
                  return this.imask_instance && this.dependenciesFulfilled && this.options.imask.returnUnmasked ? this.imask_instance.unmaskedValue : Ot(At(o.prototype), 'getValue', this).call(this);
              },
            },
            {
              key: 'enable',
              value: function() {
                this.always_disabled || ((this.input.disabled = !1), Ot(At(o.prototype), 'enable', this).call(this));
              },
            },
            {
              key: 'disable',
              value: function(t) {
                t && (this.always_disabled = !0), (this.input.disabled = !0), Ot(At(o.prototype), 'disable', this).call(this);
              },
            },
            {
              key: 'afterInputReady',
              value: function() {
                this.theme.afterInputReady(this.input), window.Cleave && !this.cleave_instance ? this.setupCleave(this.input) : window.IMask && !this.imask_instance && this.setupImask(this.input);
              },
            },
            {
              key: 'refreshValue',
              value: function() {
                (this.value = this.input.value), 'string' == typeof this.value || this.shouldBeUnset() || (this.value = ''), (this.serialized = this.value);
              },
            },
            {
              key: 'destroy',
              value: function() {
                this.cleave_instance && this.cleave_instance.destroy(),
                  this.imask_instance && this.imask_instance.destroy(),
                  (this.template = null),
                  this.input && this.input.parentNode && this.input.parentNode.removeChild(this.input),
                  this.label && this.label.parentNode && this.label.parentNode.removeChild(this.label),
                  this.description && this.description.parentNode && this.description.parentNode.removeChild(this.description),
                  Ot(At(o.prototype), 'destroy', this).call(this);
              },
            },
            {
              key: 'sanitize',
              value: function(t) {
                return t;
              },
            },
            {
              key: 'onWatchedFieldChange',
              value: function() {
                var t;
                this.template && ((t = this.getWatchedFieldValues()), this.setValue(this.template(t), !1, !0)), Ot(At(o.prototype), 'onWatchedFieldChange', this).call(this);
              },
            },
            {
              key: 'showValidationErrors',
              value: function(t) {
                var e = this;
                if ('always' === this.jsoneditor.options.show_errors);
                else if (!this.is_dirty && this.previous_error_setting === this.jsoneditor.options.show_errors) return;
                this.previous_error_setting = this.jsoneditor.options.show_errors;
                var r = t.reduce(function(t, r) {
                  return r.path === e.path && t.push(r.message), t;
                }, []);
                r.length ? this.theme.addInputError(this.input, ''.concat(r.join('. '), '.')) : this.theme.removeInputError(this.input);
              },
            },
          ]) && jt(e.prototype, r),
          n && jt(e, n),
          o
        );
      })(M);
      function Tt(t) {
        return (Tt =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function Rt(t, e) {
        if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
      }
      function It(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      function Lt(t, e, r) {
        return (Lt =
          'undefined' != typeof Reflect && Reflect.get
            ? Reflect.get
            : function(t, e, r) {
                var n = (function(t, e) {
                  for (; !Object.prototype.hasOwnProperty.call(t, e) && null !== (t = Dt(t)); );
                  return t;
                })(t, e);
                if (n) {
                  var i = Object.getOwnPropertyDescriptor(n, e);
                  return i.get ? i.get.call(r) : i.value;
                }
              })(t, e, r || t);
      }
      function Nt(t, e) {
        return (Nt =
          Object.setPrototypeOf ||
          function(t, e) {
            return (t.__proto__ = e), t;
          })(t, e);
      }
      function Bt(t) {
        var e = (function() {
          if ('undefined' == typeof Reflect || !Reflect.construct) return !1;
          if (Reflect.construct.sham) return !1;
          if ('function' == typeof Proxy) return !0;
          try {
            return Boolean.prototype.valueOf.call(Reflect.construct(Boolean, [], function() {})), !0;
          } catch (t) {
            return !1;
          }
        })();
        return function() {
          var r,
            n = Dt(t);
          if (e) {
            var i = Dt(this).constructor;
            r = Reflect.construct(n, arguments, i);
          } else r = n.apply(this, arguments);
          return Vt(this, r);
        };
      }
      function Vt(t, e) {
        return !e || ('object' !== Tt(e) && 'function' != typeof e)
          ? (function(t) {
              if (void 0 === t) throw new ReferenceError("this hasn't been initialised - super() hasn't been called");
              return t;
            })(t)
          : e;
      }
      function Dt(t) {
        return (Dt = Object.setPrototypeOf
          ? Object.getPrototypeOf
          : function(t) {
              return t.__proto__ || Object.getPrototypeOf(t);
            })(t);
      }
      var Ft = (function(t) {
        !(function(t, e) {
          if ('function' != typeof e && null !== e) throw new TypeError('Super expression must either be null or a function');
          (t.prototype = Object.create(e && e.prototype, { constructor: { value: t, writable: !0, configurable: !0 } })), e && Nt(t, e);
        })(o, t);
        var e,
          r,
          n,
          i = Bt(o);
        function o() {
          return Rt(this, o), i.apply(this, arguments);
        }
        return (
          (e = o),
          (r = [
            {
              key: 'build',
              value: function() {
                if ((Lt(Dt(o.prototype), 'build', this).call(this), void 0 !== this.schema.minimum)) {
                  var t = this.schema.minimum;
                  void 0 !== this.schema.exclusiveMinimum && (t += 1), this.input.setAttribute('min', t);
                }
                if (void 0 !== this.schema.maximum) {
                  var e = this.schema.maximum;
                  void 0 !== this.schema.exclusiveMaximum && (e -= 1), this.input.setAttribute('max', e);
                }
                if (void 0 !== this.schema.step) {
                  var r = this.schema.step || 1;
                  this.input.setAttribute('step', r);
                }
                this.setInputAttributes(['maxlength', 'pattern', 'readonly', 'min', 'max', 'step']);
              },
            },
            {
              key: 'getNumColumns',
              value: function() {
                return 2;
              },
            },
            {
              key: 'getValue',
              value: function() {
                if (this.dependenciesFulfilled) {
                  var t = (function(t) {
                    if (null == t) return !1;
                    var e = t.match(b),
                      r = parseFloat(t);
                    return null !== e && !isNaN(r) && isFinite(r);
                  })(this.value)
                    ? parseFloat(this.value)
                    : this.value;
                  if (this.jsoneditor.options.use_default_values || '' !== t) return t;
                }
              },
            },
          ]) && It(e.prototype, r),
          n && It(e, n),
          o
        );
      })(Pt);
      function Mt(t) {
        return (Mt =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function Ht(t, e) {
        if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
      }
      function qt(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      function Ut(t, e) {
        return (Ut =
          Object.setPrototypeOf ||
          function(t, e) {
            return (t.__proto__ = e), t;
          })(t, e);
      }
      function zt(t) {
        var e = (function() {
          if ('undefined' == typeof Reflect || !Reflect.construct) return !1;
          if (Reflect.construct.sham) return !1;
          if ('function' == typeof Proxy) return !0;
          try {
            return Boolean.prototype.valueOf.call(Reflect.construct(Boolean, [], function() {})), !0;
          } catch (t) {
            return !1;
          }
        })();
        return function() {
          var r,
            n = Jt(t);
          if (e) {
            var i = Jt(this).constructor;
            r = Reflect.construct(n, arguments, i);
          } else r = n.apply(this, arguments);
          return $t(this, r);
        };
      }
      function $t(t, e) {
        return !e || ('object' !== Mt(e) && 'function' != typeof e)
          ? (function(t) {
              if (void 0 === t) throw new ReferenceError("this hasn't been initialised - super() hasn't been called");
              return t;
            })(t)
          : e;
      }
      function Jt(t) {
        return (Jt = Object.setPrototypeOf
          ? Object.getPrototypeOf
          : function(t) {
              return t.__proto__ || Object.getPrototypeOf(t);
            })(t);
      }
      var Gt = (function(t) {
        !(function(t, e) {
          if ('function' != typeof e && null !== e) throw new TypeError('Super expression must either be null or a function');
          (t.prototype = Object.create(e && e.prototype, { constructor: { value: t, writable: !0, configurable: !0 } })), e && Ut(t, e);
        })(o, t);
        var e,
          r,
          n,
          i = zt(o);
        function o() {
          return Ht(this, o), i.apply(this, arguments);
        }
        return (
          (e = o),
          (r = [
            {
              key: 'getNumColumns',
              value: function() {
                return 2;
              },
            },
            {
              key: 'getValue',
              value: function() {
                if (this.dependenciesFulfilled) {
                  var t = (function(t) {
                    if (null == t) return !1;
                    var e = t.match(g),
                      r = parseInt(t);
                    return null !== e && !isNaN(r) && isFinite(r);
                  })(this.value)
                    ? parseInt(this.value)
                    : this.value;
                  if (this.jsoneditor.options.use_default_values || '' !== t) return t;
                }
              },
            },
          ]) && qt(e.prototype, r),
          n && qt(e, n),
          o
        );
      })(Ft);
      function Wt(t) {
        return (Wt =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function Yt(t, e) {
        if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
      }
      function Xt(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      function Kt(t, e, r) {
        return (Kt =
          'undefined' != typeof Reflect && Reflect.get
            ? Reflect.get
            : function(t, e, r) {
                var n = (function(t, e) {
                  for (; !Object.prototype.hasOwnProperty.call(t, e) && null !== (t = ee(t)); );
                  return t;
                })(t, e);
                if (n) {
                  var i = Object.getOwnPropertyDescriptor(n, e);
                  return i.get ? i.get.call(r) : i.value;
                }
              })(t, e, r || t);
      }
      function Zt(t, e) {
        return (Zt =
          Object.setPrototypeOf ||
          function(t, e) {
            return (t.__proto__ = e), t;
          })(t, e);
      }
      function Qt(t) {
        var e = (function() {
          if ('undefined' == typeof Reflect || !Reflect.construct) return !1;
          if (Reflect.construct.sham) return !1;
          if ('function' == typeof Proxy) return !0;
          try {
            return Boolean.prototype.valueOf.call(Reflect.construct(Boolean, [], function() {})), !0;
          } catch (t) {
            return !1;
          }
        })();
        return function() {
          var r,
            n = ee(t);
          if (e) {
            var i = ee(this).constructor;
            r = Reflect.construct(n, arguments, i);
          } else r = n.apply(this, arguments);
          return te(this, r);
        };
      }
      function te(t, e) {
        return !e || ('object' !== Wt(e) && 'function' != typeof e)
          ? (function(t) {
              if (void 0 === t) throw new ReferenceError("this hasn't been initialised - super() hasn't been called");
              return t;
            })(t)
          : e;
      }
      function ee(t) {
        return (ee = Object.setPrototypeOf
          ? Object.getPrototypeOf
          : function(t) {
              return t.__proto__ || Object.getPrototypeOf(t);
            })(t);
      }
      var re = (function(t) {
        !(function(t, e) {
          if ('function' != typeof e && null !== e) throw new TypeError('Super expression must either be null or a function');
          (t.prototype = Object.create(e && e.prototype, { constructor: { value: t, writable: !0, configurable: !0 } })), e && Zt(t, e);
        })(o, t);
        var e,
          r,
          n,
          i = Qt(o);
        function o() {
          return Yt(this, o), i.apply(this, arguments);
        }
        return (
          (e = o),
          (r = [
            {
              key: 'register',
              value: function() {
                if (this.editors) {
                  for (var t = 0; t < this.editors.length; t++) this.editors[t] && this.editors[t].unregister();
                  this.editors[this.type] && this.editors[this.type].register();
                }
                Kt(ee(o.prototype), 'register', this).call(this);
              },
            },
            {
              key: 'unregister',
              value: function() {
                if ((Kt(ee(o.prototype), 'unregister', this).call(this), this.editors)) for (var t = 0; t < this.editors.length; t++) this.editors[t] && this.editors[t].unregister();
              },
            },
            {
              key: 'getNumColumns',
              value: function() {
                return this.editors[this.type] ? Math.max(this.editors[this.type].getNumColumns(), 4) : 4;
              },
            },
            {
              key: 'enable',
              value: function() {
                if (!this.always_disabled) {
                  if (this.editors) for (var t = 0; t < this.editors.length; t++) this.editors[t] && this.editors[t].enable();
                  (this.switcher.disabled = !1), Kt(ee(o.prototype), 'enable', this).call(this);
                }
              },
            },
            {
              key: 'disable',
              value: function(t) {
                if ((t && (this.always_disabled = !0), this.editors)) for (var e = 0; e < this.editors.length; e++) this.editors[e] && this.editors[e].disable(t);
                (this.switcher.disabled = !0), Kt(ee(o.prototype), 'disable', this).call(this);
              },
            },
            {
              key: 'switchEditor',
              value: function(t) {
                var e = this;
                this.editors[t] || this.buildChildEditor(t);
                var r = this.getValue();
                (this.type = t),
                  this.register(),
                  this.editors.forEach(function(t, n) {
                    t && (e.type === n ? (e.keep_values && t.setValue(r, !0), (t.container.style.display = '')) : (t.container.style.display = 'none'));
                  }),
                  this.refreshValue(),
                  this.refreshHeaderText();
              },
            },
            {
              key: 'buildChildEditor',
              value: function(t) {
                var e,
                  r = this,
                  n = this.types[t],
                  i = this.theme.getChildEditorHolder();
                this.editor_holder.appendChild(i),
                  'string' == typeof n
                    ? ((e = f({}, this.schema)).type = n)
                    : ((e = f({}, this.schema, n)),
                      (e = this.jsoneditor.expandRefs(e)),
                      n && n.required && Array.isArray(n.required) && this.schema.required && Array.isArray(this.schema.required) && (e.required = this.schema.required.concat(n.required)));
                var o = this.jsoneditor.getEditorClass(e);
                (this.editors[t] = this.jsoneditor.createEditor(o, { jsoneditor: this.jsoneditor, schema: e, container: i, path: this.path, parent: this, required: !0 })),
                  this.editors[t].preBuild(),
                  this.editors[t].build(),
                  this.editors[t].postBuild(),
                  this.editors[t].header && (this.editors[t].header.style.display = 'none'),
                  (this.editors[t].option = this.switcher_options[t]),
                  i.addEventListener('change_header_text', function() {
                    r.refreshHeaderText();
                  }),
                  t !== this.type && (i.style.display = 'none');
              },
            },
            {
              key: 'preBuild',
              value: function() {
                if (
                  ((this.types = []),
                  (this.type = 0),
                  (this.editors = []),
                  (this.validators = []),
                  (this.keep_values = !0),
                  void 0 !== this.jsoneditor.options.keep_oneof_values && (this.keep_values = this.jsoneditor.options.keep_oneof_values),
                  void 0 !== this.options.keep_oneof_values && (this.keep_values = this.options.keep_oneof_values),
                  this.schema.oneOf)
                )
                  (this.oneOf = !0), (this.types = this.schema.oneOf), delete this.schema.oneOf;
                else if (this.schema.anyOf) (this.anyOf = !0), (this.types = this.schema.anyOf), delete this.schema.anyOf;
                else {
                  if (this.schema.type && 'any' !== this.schema.type) Array.isArray(this.schema.type) ? (this.types = this.schema.type) : (this.types = [this.schema.type]);
                  else if (((this.types = ['string', 'number', 'integer', 'boolean', 'object', 'array', 'null']), this.schema.disallow)) {
                    var t = this.schema.disallow;
                    ('object' === Wt(t) && Array.isArray(t)) || (t = [t]);
                    var e = [];
                    this.types.forEach(function(r) {
                      t.includes(r) || e.push(r);
                    }),
                      (this.types = e);
                  }
                  delete this.schema.type;
                }
                this.display_text = this.getDisplayText(this.types);
              },
            },
            {
              key: 'build',
              value: function() {
                var t = this,
                  e = this.container;
                (this.header = this.label = this.theme.getFormInputLabel(this.getTitle(), this.isRequired())),
                  this.container.appendChild(this.header),
                  (this.switcher = this.theme.getSwitcher(this.display_text)),
                  this.switcher.setAttribute('tabIndex', '-1'),
                  e.appendChild(this.switcher),
                  this.switcher.addEventListener('change', function(e) {
                    e.preventDefault(), e.stopPropagation(), t.switchEditor(t.display_text.indexOf(e.currentTarget.value)), t.onChange(!0);
                  }),
                  (this.editor_holder = document.createElement('div')),
                  e.appendChild(this.editor_holder);
                var r = {};
                this.jsoneditor.options.custom_validators && (r.custom_validators = this.jsoneditor.options.custom_validators),
                  (this.switcher_options = this.theme.getSwitcherOptions(this.switcher)),
                  this.types.forEach(function(e, n) {
                    var i;
                    (t.editors[n] = !1),
                      'string' == typeof e
                        ? ((i = f({}, t.schema)).type = e)
                        : ((i = f({}, t.schema, e)),
                          e.required && Array.isArray(e.required) && t.schema.required && Array.isArray(t.schema.required) && (i.required = t.schema.required.concat(e.required))),
                      (t.validators[n] = new P(t.jsoneditor, i, r, t.defaults));
                  }),
                  this.switchEditor(0);
              },
            },
            {
              key: 'onChildEditorChange',
              value: function(t) {
                this.editors[this.type] && (this.refreshValue(), this.refreshHeaderText()), Kt(ee(o.prototype), 'onChildEditorChange', this).call(this);
              },
            },
            {
              key: 'refreshHeaderText',
              value: function() {
                var t = this.getDisplayText(this.types);
                Array.from(this.switcher_options).forEach(function(e, r) {
                  e.textContent = t[r];
                });
              },
            },
            {
              key: 'refreshValue',
              value: function() {
                this.value = this.editors[this.type].getValue();
              },
            },
            {
              key: 'setValue',
              value: function(t, e) {
                var r = this,
                  n = this.type,
                  i = { match: 0, extra: 0, i: this.type },
                  o = { match: 0, i: null };
                this.validators.forEach(function(e, n) {
                  var a = null;
                  void 0 !== r.anyOf && r.anyOf && ((a = e.fitTest(t)), (i.match < a.match || (i.match === a.match && i.extra > a.extra)) && ((i = a).i = n)),
                    e.validate(t).length || null !== o.i ? (i = o) : ((o.i = n), null !== a && (o.match = a.match));
                });
                var a = o.i;
                void 0 !== this.anyOf && this.anyOf && o.match < i.match && (a = i.i), null === a && (a = this.type), (this.type = a), (this.switcher.value = this.display_text[a]);
                var s = this.type !== n;
                s && this.switchEditor(this.type), this.editors[this.type].setValue(t, e), this.refreshValue(), this.onChange(s);
              },
            },
            {
              key: 'destroy',
              value: function() {
                this.editors.forEach(function(t) {
                  t && t.destroy();
                }),
                  this.editor_holder && this.editor_holder.parentNode && this.editor_holder.parentNode.removeChild(this.editor_holder),
                  this.switcher && this.switcher.parentNode && this.switcher.parentNode.removeChild(this.switcher),
                  Kt(ee(o.prototype), 'destroy', this).call(this);
              },
            },
            {
              key: 'showValidationErrors',
              value: function(t) {
                var e = this;
                if (this.oneOf || this.anyOf) {
                  var r = this.oneOf ? 'oneOf' : 'anyOf';
                  this.editors.forEach(function(n, i) {
                    if (n) {
                      var o = ''
                        .concat(e.path, '.')
                        .concat(r, '[')
                        .concat(i, ']');
                      n.showValidationErrors(
                        t.reduce(function(t, r) {
                          if (r.path.startsWith(o) || r.path === o.substr(0, r.path.length)) {
                            var n = f({}, r);
                            r.path.startsWith(o) && (n.path = e.path + n.path.substr(o.length)), t.push(n);
                          }
                          return t;
                        }, [])
                      );
                    }
                  });
                } else
                  this.editors.forEach(function(e) {
                    e && e.showValidationErrors(t);
                  });
              },
            },
            { key: 'addLinks', value: function() {} },
          ]) && Xt(e.prototype, r),
          n && Xt(e, n),
          o
        );
      })(M);
      r(157);
      function ne(t, e) {
        var r = Object.keys(t);
        if (Object.getOwnPropertySymbols) {
          var n = Object.getOwnPropertySymbols(t);
          e &&
            (n = n.filter(function(e) {
              return Object.getOwnPropertyDescriptor(t, e).enumerable;
            })),
            r.push.apply(r, n);
        }
        return r;
      }
      function ie(t) {
        for (var e = 1; e < arguments.length; e++) {
          var r = null != arguments[e] ? arguments[e] : {};
          e % 2
            ? ne(Object(r), !0).forEach(function(e) {
                oe(t, e, r[e]);
              })
            : Object.getOwnPropertyDescriptors
            ? Object.defineProperties(t, Object.getOwnPropertyDescriptors(r))
            : ne(Object(r)).forEach(function(e) {
                Object.defineProperty(t, e, Object.getOwnPropertyDescriptor(r, e));
              });
        }
        return t;
      }
      function oe(t, e, r) {
        return e in t ? Object.defineProperty(t, e, { value: r, enumerable: !0, configurable: !0, writable: !0 }) : (t[e] = r), t;
      }
      function ae(t, e) {
        return (
          (function(t) {
            if (Array.isArray(t)) return t;
          })(t) ||
          (function(t, e) {
            var r = t && (('undefined' != typeof Symbol && t[Symbol.iterator]) || t['@@iterator']);
            if (null == r) return;
            var n,
              i,
              o = [],
              a = !0,
              s = !1;
            try {
              for (r = r.call(t); !(a = (n = r.next()).done) && (o.push(n.value), !e || o.length !== e); a = !0);
            } catch (t) {
              (s = !0), (i = t);
            } finally {
              try {
                a || null == r.return || r.return();
              } finally {
                if (s) throw i;
              }
            }
            return o;
          })(t, e) ||
          (function(t, e) {
            if (!t) return;
            if ('string' == typeof t) return se(t, e);
            var r = Object.prototype.toString.call(t).slice(8, -1);
            'Object' === r && t.constructor && (r = t.constructor.name);
            if ('Map' === r || 'Set' === r) return Array.from(t);
            if ('Arguments' === r || /^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(r)) return se(t, e);
          })(t, e) ||
          (function() {
            throw new TypeError('Invalid attempt to destructure non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.');
          })()
        );
      }
      function se(t, e) {
        (null == e || e > t.length) && (e = t.length);
        for (var r = 0, n = new Array(e); r < e; r++) n[r] = t[r];
        return n;
      }
      function le(t) {
        return (le =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function ce(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      function ue(t, e, r) {
        return (ue =
          'undefined' != typeof Reflect && Reflect.get
            ? Reflect.get
            : function(t, e, r) {
                var n = (function(t, e) {
                  for (; !Object.prototype.hasOwnProperty.call(t, e) && null !== (t = fe(t)); );
                  return t;
                })(t, e);
                if (n) {
                  var i = Object.getOwnPropertyDescriptor(n, e);
                  return i.get ? i.get.call(r) : i.value;
                }
              })(t, e, r || t);
      }
      function he(t, e) {
        return (he =
          Object.setPrototypeOf ||
          function(t, e) {
            return (t.__proto__ = e), t;
          })(t, e);
      }
      function de(t) {
        var e = (function() {
          if ('undefined' == typeof Reflect || !Reflect.construct) return !1;
          if (Reflect.construct.sham) return !1;
          if ('function' == typeof Proxy) return !0;
          try {
            return Boolean.prototype.valueOf.call(Reflect.construct(Boolean, [], function() {})), !0;
          } catch (t) {
            return !1;
          }
        })();
        return function() {
          var r,
            n = fe(t);
          if (e) {
            var i = fe(this).constructor;
            r = Reflect.construct(n, arguments, i);
          } else r = n.apply(this, arguments);
          return pe(this, r);
        };
      }
      function pe(t, e) {
        return !e || ('object' !== le(e) && 'function' != typeof e)
          ? (function(t) {
              if (void 0 === t) throw new ReferenceError("this hasn't been initialised - super() hasn't been called");
              return t;
            })(t)
          : e;
      }
      function fe(t) {
        return (fe = Object.setPrototypeOf
          ? Object.getPrototypeOf
          : function(t) {
              return t.__proto__ || Object.getPrototypeOf(t);
            })(t);
      }
      var ye = (function(t) {
        !(function(t, e) {
          if ('function' != typeof e && null !== e) throw new TypeError('Super expression must either be null or a function');
          (t.prototype = Object.create(e && e.prototype, { constructor: { value: t, writable: !0, configurable: !0 } })), e && he(t, e);
        })(o, t);
        var e,
          r,
          n,
          i = de(o);
        function o(t, e, r) {
          var n;
          return (
            (function(t, e) {
              if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
            })(this, o),
            ((n = i.call(this, t, e)).currentDepth = r),
            n
          );
        }
        return (
          (e = o),
          (r = [
            {
              key: 'getTemplatePathForChild',
              value: function(t) {
                return '' === this.template_path ? t : ':' === this.template_path.slice(-1) ? ''.concat(this.template_path, ':').concat(t) : ''.concat(this.template_path, '.').concat(t);
              },
            },
            {
              key: 'getDefault',
              value: function() {
                return f({}, this.schema.default || {});
              },
            },
            {
              key: 'getChildEditors',
              value: function() {
                return this.editors;
              },
            },
            {
              key: 'register',
              value: function() {
                ue(fe(o.prototype), 'register', this).call(this),
                  this.editors &&
                    Object.values(this.editors).forEach(function(t) {
                      return t.register();
                    });
              },
            },
            {
              key: 'unregister',
              value: function() {
                ue(fe(o.prototype), 'unregister', this).call(this),
                  this.editors &&
                    Object.values(this.editors).forEach(function(t) {
                      return t.unregister();
                    });
              },
            },
            {
              key: 'getNumColumns',
              value: function() {
                return Math.max(Math.min(12, this.maxwidth), 3);
              },
            },
            {
              key: 'enable',
              value: function() {
                this.always_disabled ||
                  (this.editjson_control && (this.editjson_control.disabled = !1),
                  this.addproperty_button && (this.addproperty_button.disabled = !1),
                  ue(fe(o.prototype), 'enable', this).call(this),
                  this.editors &&
                    Object.values(this.editors).forEach(function(t) {
                      t.isActive() && t.enable(), (t.optInCheckbox.disabled = !1);
                    }));
              },
            },
            {
              key: 'disable',
              value: function(t) {
                t && (this.always_disabled = !0),
                  this.editjson_control && (this.editjson_control.disabled = !0),
                  this.addproperty_button && (this.addproperty_button.disabled = !0),
                  this.hideEditJSON(),
                  ue(fe(o.prototype), 'disable', this).call(this),
                  this.editors &&
                    Object.values(this.editors).forEach(function(e) {
                      e.isActive() && e.disable(t), (e.optInCheckbox.disabled = !0);
                    });
              },
            },
            {
              key: 'layoutEditors',
              value: function() {
                var t,
                  e,
                  r = this;
                if (this.row_container) {
                  var n;
                  (this.property_order = Object.keys(this.editors)),
                    (this.property_order = this.property_order.sort(function(t, e) {
                      var n = r.editors[t].schema.propertyOrder,
                        i = r.editors[e].schema.propertyOrder;
                      return 'number' != typeof n && (n = 1e3), 'number' != typeof i && (i = 1e3), n - i;
                    }));
                  var i,
                    o = 'categories' === this.format,
                    a = [],
                    s = null,
                    l = null;
                  if ('grid-strict' === this.format) {
                    var c = 0;
                    if (
                      ((i = []),
                      this.property_order.forEach(function(t) {
                        var e = r.editors[t];
                        if (!e.property_removed) {
                          var n = e.options.hidden ? 0 : e.options.grid_columns || e.getNumColumns(),
                            o = e.options.hidden ? 0 : e.options.grid_offset || 0,
                            s = !e.options.hidden && (e.options.grid_break || !1),
                            l = { key: t, width: n, offset: o, height: e.options.hidden ? 0 : e.container.offsetHeight };
                          i.push(l), (a[c] = i), s && (c++, (i = []));
                        }
                      }),
                      this.layout === JSON.stringify(a))
                    )
                      return !1;
                    for (this.layout = JSON.stringify(a), n = document.createElement('div'), t = 0; t < a.length; t++)
                      for (i = this.theme.getGridRow(), n.appendChild(i), e = 0; e < a[t].length; e++)
                        (s = a[t][e].key),
                          (l = this.editors[s]).options.hidden ? (l.container.style.display = 'none') : this.theme.setGridColumnSize(l.container, a[t][e].width, a[t][e].offset),
                          i.appendChild(l.container);
                  } else if ('grid' === this.format) {
                    for (
                      this.property_order.forEach(function(t) {
                        var e = r.editors[t];
                        if (!e.property_removed) {
                          for (var n = !1, i = e.options.hidden ? 0 : e.options.grid_columns || e.getNumColumns(), o = e.options.hidden ? 0 : e.container.offsetHeight, s = 0; s < a.length; s++)
                            a[s].width + i <= 12 && (!o || (0.5 * a[s].minh < o && 2 * a[s].maxh > o)) && (n = s);
                          !1 === n && (a.push({ width: 0, minh: 999999, maxh: 0, editors: [] }), (n = a.length - 1)),
                            a[n].editors.push({ key: t, width: i, height: o }),
                            (a[n].width += i),
                            (a[n].minh = Math.min(a[n].minh, o)),
                            (a[n].maxh = Math.max(a[n].maxh, o));
                        }
                      }),
                        t = 0;
                      t < a.length;
                      t++
                    )
                      if (a[t].width < 12) {
                        var u = !1,
                          h = 0;
                        for (e = 0; e < a[t].editors.length; e++)
                          (!1 === u || a[t].editors[e].width > a[t].editors[u].width) && (u = e),
                            (a[t].editors[e].width *= 12 / a[t].width),
                            (a[t].editors[e].width = Math.floor(a[t].editors[e].width)),
                            (h += a[t].editors[e].width);
                        h < 12 && (a[t].editors[u].width += 12 - h), (a[t].width = 12);
                      }
                    if (this.layout === JSON.stringify(a)) return !1;
                    for (this.layout = JSON.stringify(a), n = document.createElement('div'), t = 0; t < a.length; t++)
                      for (i = this.theme.getGridRow(), n.appendChild(i), e = 0; e < a[t].editors.length; e++)
                        (s = a[t].editors[e].key),
                          (l = this.editors[s]).options.hidden ? (l.container.style.display = 'none') : this.theme.setGridColumnSize(l.container, a[t].editors[e].width),
                          i.appendChild(l.container);
                  } else {
                    if (((n = document.createElement('div')), o)) {
                      var d = document.createElement('div'),
                        p = this.theme.getTopTabHolder(this.translateProperty(this.schema.title)),
                        f = this.theme.getTopTabContentHolder(p);
                      for (
                        this.property_order.forEach(function(t) {
                          var e = r.editors[t];
                          if (!e.property_removed) {
                            var n = r.theme.getTabContent(),
                              i = e.schema && ('object' === e.schema.type || 'array' === e.schema.type);
                            n.isObjOrArray = i;
                            var o = r.theme.getGridRow();
                            e.tab || (void 0 === r.basicPane ? r.addRow(e, p, n) : r.addRow(e, p, r.basicPane)),
                              (n.id = r.getValidId(e.tab_text.textContent)),
                              i
                                ? (n.appendChild(o), f.appendChild(n), r.theme.addTopTab(p, e.tab))
                                : (d.appendChild(o),
                                  f.childElementCount > 0
                                    ? f.firstChild.isObjOrArray && (n.appendChild(d), f.insertBefore(n, f.firstChild), r.theme.insertBasicTopTab(e.tab, p), (e.basicPane = n))
                                    : (n.appendChild(d), f.appendChild(n), r.theme.addTopTab(p, e.tab), (e.basicPane = n))),
                              e.options.hidden ? (e.container.style.display = 'none') : r.theme.setGridColumnSize(e.container, 12),
                              o.appendChild(e.container),
                              (e.rowPane = n);
                          }
                        });
                        this.tabPanesContainer.firstChild;

                      )
                        this.tabPanesContainer.removeChild(this.tabPanesContainer.firstChild);
                      var m = this.tabs_holder.parentNode;
                      m.removeChild(m.firstChild), m.appendChild(p), (this.tabPanesContainer = f), (this.tabs_holder = p);
                      var v = this.theme.getFirstTab(this.tabs_holder);
                      return void (v && y(v, 'click'));
                    }
                    this.property_order.forEach(function(t) {
                      var e = r.editors[t];
                      e.property_removed ||
                        ((i = r.theme.getGridRow()),
                        n.appendChild(i),
                        e.options.hidden ? (e.container.style.display = 'none') : r.theme.setGridColumnSize(e.container, 12),
                        i.appendChild(e.container));
                    });
                  }
                  for (; this.row_container.firstChild; ) this.row_container.removeChild(this.row_container.firstChild);
                  this.row_container.appendChild(n);
                }
              },
            },
            {
              key: 'getPropertySchema',
              value: function(t) {
                var e = this,
                  r = this.schema.properties[t] || {};
                r = f({}, r);
                var n = !!this.schema.properties[t];
                return (
                  this.schema.patternProperties &&
                    Object.keys(this.schema.patternProperties).forEach(function(i) {
                      new RegExp(i).test(t) && ((r.allOf = r.allOf || []), r.allOf.push(e.schema.patternProperties[i]), (n = !0));
                    }),
                  !n && this.schema.additionalProperties && 'object' === le(this.schema.additionalProperties) && (r = f({}, this.schema.additionalProperties)),
                  r
                );
              },
            },
            {
              key: 'preBuild',
              value: function() {
                var t = this;
                if (
                  (ue(fe(o.prototype), 'preBuild', this).call(this),
                  (this.editors = {}),
                  (this.cached_editors = {}),
                  (this.format = this.options.layout || this.options.object_layout || this.schema.format || this.jsoneditor.options.object_layout || 'normal'),
                  (this.schema.properties = this.schema.properties || {}),
                  (this.minwidth = 0),
                  (this.maxwidth = 0),
                  this.options.table_row)
                )
                  Object.entries(this.schema.properties).forEach(function(e) {
                    var r = ae(e, 2),
                      n = r[0],
                      i = r[1],
                      o = t.jsoneditor.getEditorClass(i);
                    (t.editors[n] = t.jsoneditor.createEditor(
                      o,
                      { jsoneditor: t.jsoneditor, schema: i, path: ''.concat(t.path, '.').concat(n), template_path: t.getTemplatePathForChild(n), parent: t, compact: !0, required: !0 },
                      t.currentDepth + 1
                    )),
                      t.editors[n].preBuild();
                    var a = t.editors[n].options.hidden ? 0 : t.editors[n].options.grid_columns || t.editors[n].getNumColumns();
                    (t.minwidth += a), (t.maxwidth += a);
                  }),
                    (this.no_link_holder = !0);
                else {
                  if (this.options.table) throw new Error('Not supported yet');
                  this.schema.defaultProperties ||
                    (this.jsoneditor.options.display_required_only || this.options.display_required_only
                      ? (this.schema.defaultProperties = Object.keys(this.schema.properties).filter(function(e) {
                          return t.isRequiredObject({ key: e, schema: t.schema.properties[e] });
                        }))
                      : (this.schema.defaultProperties = Object.keys(this.schema.properties))),
                    (this.maxwidth += 1),
                    Array.isArray(this.schema.defaultProperties) &&
                      this.schema.defaultProperties.forEach(function(e) {
                        t.addObjectProperty(e, !0),
                          t.editors[e] &&
                            ((t.minwidth = Math.max(t.minwidth, t.editors[e].options.grid_columns || t.editors[e].getNumColumns())),
                            (t.maxwidth += t.editors[e].options.grid_columns || t.editors[e].getNumColumns()));
                      });
                }
                (this.property_order = Object.keys(this.editors)),
                  (this.property_order = this.property_order.sort(function(e, r) {
                    var n = t.editors[e].schema.propertyOrder,
                      i = t.editors[r].schema.propertyOrder;
                    return 'number' != typeof n && (n = 1e3), 'number' != typeof i && (i = 1e3), n - i;
                  }));
              },
            },
            {
              key: 'addTab',
              value: function(t) {
                var e = this,
                  r = this.rows[t].schema && ('object' === this.rows[t].schema.type || 'array' === this.rows[t].schema.type);
                this.tabs_holder &&
                  ((this.rows[t].tab_text = document.createElement('span')),
                  (this.rows[t].tab_text.textContent = r ? this.rows[t].getHeaderText() : void 0 === this.schema.basicCategoryTitle ? 'Basic' : this.schema.basicCategoryTitle),
                  (this.rows[t].tab = this.theme.getTopTab(this.rows[t].tab_text, this.getValidId(this.rows[t].tab_text.textContent))),
                  this.rows[t].tab.addEventListener('click', function(r) {
                    (e.active_tab = e.rows[t].tab), e.refreshTabs(), r.preventDefault(), r.stopPropagation();
                  }));
              },
            },
            {
              key: 'addRow',
              value: function(t, e, r) {
                var n = this.rows.length,
                  i = 'object' === t.schema.type || 'array' === t.schema.type;
                (this.rows[n] = t),
                  (this.rows[n].rowPane = r),
                  i
                    ? (this.addTab(n), this.theme.addTopTab(e, this.rows[n].tab))
                    : void 0 === this.basicTab
                    ? (this.addTab(n), (this.basicTab = n), (this.basicPane = r), this.theme.addTopTab(e, this.rows[n].tab))
                    : ((this.rows[n].tab = this.rows[this.basicTab].tab), (this.rows[n].tab_text = this.rows[this.basicTab].tab_text), (this.rows[n].rowPane = this.rows[this.basicTab].rowPane));
              },
            },
            {
              key: 'refreshTabs',
              value: function(t) {
                var e = this,
                  r = void 0 !== this.basicTab,
                  n = !1;
                this.rows.forEach(function(i) {
                  i.tab &&
                    i.rowPane &&
                    i.rowPane.parentNode &&
                    ((r && i.tab === e.rows[e.basicTab].tab && n) ||
                      (t
                        ? (i.tab_text.textContent = i.getHeaderText())
                        : (r && i.tab === e.rows[e.basicTab].tab && (n = !0), i.tab === e.active_tab ? e.theme.markTabActive(i) : e.theme.markTabInactive(i))));
                });
              },
            },
            {
              key: 'build',
              value: function() {
                var t = this,
                  e = 'categories' === this.format;
                if (((this.rows = []), (this.active_tab = null), this.options.table_row))
                  (this.editor_holder = this.container),
                    Object.entries(this.editors).forEach(function(e) {
                      var r = ae(e, 2),
                        n = r[0],
                        i = r[1],
                        o = t.theme.getTableCell();
                      t.editor_holder.appendChild(o),
                        i.setContainer(o),
                        i.build(),
                        i.postBuild(),
                        i.setOptInCheckbox(i.header),
                        t.editors[n].options.hidden && (o.style.display = 'none'),
                        t.editors[n].options.input_width && (o.style.width = t.editors[n].options.input_width);
                    });
                else {
                  if (this.options.table) throw new Error('Not supported yet');
                  (this.header = ''),
                    this.options.compact || ((this.header = document.createElement('label')), (this.header.textContent = this.getTitle())),
                    (this.title = this.theme.getHeader(this.header, this.getPathDepth())),
                    this.title.classList.add('je-object__title'),
                    (this.controls = this.theme.getButtonHolder()),
                    this.controls.classList.add('je-object__controls'),
                    this.container.appendChild(this.title),
                    this.container.appendChild(this.controls),
                    this.container.classList.add('je-object__container'),
                    (this.editjson_holder = this.theme.getModal()),
                    (this.editjson_textarea = this.theme.getTextareaInput()),
                    this.editjson_textarea.classList.add('je-edit-json--textarea'),
                    (this.editjson_save = this.getButton('button_save', 'save', 'button_save')),
                    this.editjson_save.classList.add('json-editor-btntype-save'),
                    this.editjson_save.addEventListener('click', function(e) {
                      e.preventDefault(), e.stopPropagation(), t.saveJSON();
                    }),
                    (this.editjson_copy = this.getButton('button_copy', 'copy', 'button_copy')),
                    this.editjson_copy.classList.add('json-editor-btntype-copy'),
                    this.editjson_copy.addEventListener('click', function(e) {
                      e.preventDefault(), e.stopPropagation(), t.copyJSON();
                    }),
                    (this.editjson_cancel = this.getButton('button_cancel', 'cancel', 'button_cancel')),
                    this.editjson_cancel.classList.add('json-editor-btntype-cancel'),
                    this.editjson_cancel.addEventListener('click', function(e) {
                      e.preventDefault(), e.stopPropagation(), t.hideEditJSON();
                    }),
                    this.editjson_holder.appendChild(this.editjson_textarea);
                  var r = document.createElement('div');
                  r.classList.add('je-editjson-modal-buttons'),
                    r.appendChild(this.editjson_copy),
                    r.appendChild(this.editjson_cancel),
                    r.appendChild(this.editjson_save),
                    this.editjson_holder.appendChild(r),
                    (this.addproperty_holder = this.theme.getModal()),
                    (this.addproperty_list = document.createElement('div')),
                    this.addproperty_list.classList.add('property-selector'),
                    (this.addproperty_add = this.getButton('button_add', 'add', 'button_add')),
                    this.addproperty_add.classList.add('json-editor-btntype-add'),
                    (this.addproperty_input = this.theme.getFormInputField('text')),
                    this.addproperty_input.setAttribute('placeholder', 'Property name...'),
                    this.addproperty_input.classList.add('property-selector-input'),
                    this.addproperty_add.addEventListener('click', function(e) {
                      if ((e.preventDefault(), e.stopPropagation(), t.addproperty_input.value)) {
                        if (t.editors[t.addproperty_input.value]) return void window.alert('there is already a property with that name');
                        t.addObjectProperty(t.addproperty_input.value), t.editors[t.addproperty_input.value] && t.editors[t.addproperty_input.value].disable(), t.onChange(!0);
                      }
                    }),
                    this.addproperty_input.addEventListener('input', function(t) {
                      t.target.previousSibling.childNodes.forEach(function(e) {
                        e.innerText.includes(t.target.value) ? (e.style.display = '') : (e.style.display = 'none');
                      });
                    }),
                    this.addproperty_holder.appendChild(this.addproperty_list),
                    this.addproperty_holder.appendChild(this.addproperty_input),
                    this.addproperty_holder.appendChild(this.addproperty_add);
                  var n = document.createElement('div');
                  (n.style.clear = 'both'),
                    this.addproperty_holder.appendChild(n),
                    document.addEventListener('click', this.onOutsideModalClick.bind(this)),
                    this.schema.description && ((this.description = this.theme.getDescription(this.translateProperty(this.schema.description))), this.container.appendChild(this.description)),
                    (this.error_holder = document.createElement('div')),
                    this.container.appendChild(this.error_holder),
                    (this.editor_holder = this.theme.getIndentedPanel()),
                    this.container.appendChild(this.editor_holder),
                    (this.row_container = this.theme.getGridContainer()),
                    e
                      ? ((this.tabs_holder = this.theme.getTopTabHolder(this.getValidId(this.translateProperty(this.schema.title)))),
                        (this.tabPanesContainer = this.theme.getTopTabContentHolder(this.tabs_holder)),
                        this.editor_holder.appendChild(this.tabs_holder))
                      : ((this.tabs_holder = this.theme.getTabHolder(this.getValidId(this.translateProperty(this.schema.title)))),
                        (this.tabPanesContainer = this.theme.getTabContentHolder(this.tabs_holder)),
                        this.editor_holder.appendChild(this.row_container)),
                    Object.values(this.editors).forEach(function(r) {
                      var n = t.theme.getTabContent(),
                        i = t.theme.getGridColumn(),
                        o = !(!r.schema || ('object' !== r.schema.type && 'array' !== r.schema.type));
                      if (((n.isObjOrArray = o), e)) {
                        if (o) {
                          var a = t.theme.getGridContainer();
                          a.appendChild(i), n.appendChild(a), t.tabPanesContainer.appendChild(n), (t.row_container = a);
                        } else
                          void 0 === t.row_container_basic &&
                            ((t.row_container_basic = t.theme.getGridContainer()),
                            n.appendChild(t.row_container_basic),
                            0 === t.tabPanesContainer.childElementCount ? t.tabPanesContainer.appendChild(n) : t.tabPanesContainer.insertBefore(n, t.tabPanesContainer.childNodes[1])),
                            t.row_container_basic.appendChild(i);
                        t.addRow(r, t.tabs_holder, n), (n.id = t.getValidId(r.schema.title));
                      } else t.row_container.appendChild(i);
                      r.setContainer(i), r.build(), r.postBuild(), r.setOptInCheckbox(r.header);
                    }),
                    this.rows[0] && y(this.rows[0].tab, 'click'),
                    (this.collapsed = !1),
                    (this.collapse_control = this.getButton('', 'collapse', 'button_collapse')),
                    this.collapse_control.classList.add('json-editor-btntype-toggle'),
                    this.title.insertBefore(this.collapse_control, this.title.childNodes[0]),
                    this.collapse_control.addEventListener('click', function(e) {
                      e.preventDefault(),
                        e.stopPropagation(),
                        t.collapsed
                          ? ((t.editor_holder.style.display = ''), (t.collapsed = !1), t.setButtonText(t.collapse_control, '', 'collapse', 'button_collapse'))
                          : ((t.editor_holder.style.display = 'none'), (t.collapsed = !0), t.setButtonText(t.collapse_control, '', 'expand', 'button_expand'));
                    }),
                    this.options.collapsed && y(this.collapse_control, 'click'),
                    this.schema.options && void 0 !== this.schema.options.disable_collapse
                      ? this.schema.options.disable_collapse && (this.collapse_control.style.display = 'none')
                      : this.jsoneditor.options.disable_collapse && (this.collapse_control.style.display = 'none'),
                    (this.editjson_control = this.getButton('JSON', 'edit', 'button_edit_json')),
                    this.editjson_control.classList.add('json-editor-btntype-editjson'),
                    this.editjson_control.addEventListener('click', function(e) {
                      e.preventDefault(), e.stopPropagation(), t.toggleEditJSON();
                    }),
                    this.controls.appendChild(this.editjson_control),
                    this.controls.appendChild(this.editjson_holder),
                    this.schema.options && void 0 !== this.schema.options.disable_edit_json
                      ? this.schema.options.disable_edit_json && (this.editjson_control.style.display = 'none')
                      : this.jsoneditor.options.disable_edit_json && (this.editjson_control.style.display = 'none'),
                    (this.addproperty_button = this.getButton('properties', 'edit_properties', 'button_object_properties')),
                    this.addproperty_button.classList.add('json-editor-btntype-properties'),
                    this.addproperty_button.addEventListener('click', function(e) {
                      e.preventDefault(), e.stopPropagation(), t.toggleAddProperty();
                    }),
                    this.controls.appendChild(this.addproperty_button),
                    this.controls.insertBefore(this.addproperty_holder, this.controls.childNodes[1]),
                    this.refreshAddProperties(),
                    this.deactivateNonRequiredProperties();
                }
                this.options.table_row
                  ? ((this.editor_holder = this.container),
                    this.property_order.forEach(function(e) {
                      t.editor_holder.appendChild(t.editors[e].container);
                    }))
                  : (this.layoutEditors(), this.layoutEditors());
              },
            },
            {
              key: 'deactivateNonRequiredProperties',
              value: function() {
                var t = this,
                  e = this.jsoneditor.options.show_opt_in,
                  r = void 0 !== this.options.show_opt_in,
                  n = r && !0 === this.options.show_opt_in,
                  i = r && !1 === this.options.show_opt_in;
                (n || (!i && e) || (!r && e)) &&
                  Object.entries(this.editors).forEach(function(e) {
                    var r = ae(e, 2),
                      n = r[0],
                      i = r[1];
                    t.isRequiredObject(i) || t.editors[n].deactivate();
                  });
              },
            },
            {
              key: 'showEditJSON',
              value: function() {
                this.editjson_holder &&
                  (this.hideAddProperty(),
                  (this.editjson_holder.style.left = ''.concat(this.editjson_control.offsetLeft, 'px')),
                  (this.editjson_holder.style.top = ''.concat(this.editjson_control.offsetTop + this.editjson_control.offsetHeight, 'px')),
                  (this.editjson_textarea.value = JSON.stringify(this.getValue(), null, 2)),
                  this.disable(),
                  (this.editjson_holder.style.display = ''),
                  (this.editjson_control.disabled = !1),
                  (this.editing_json = !0));
              },
            },
            {
              key: 'hideEditJSON',
              value: function() {
                this.editjson_holder && this.editing_json && ((this.editjson_holder.style.display = 'none'), this.enable(), (this.editing_json = !1));
              },
            },
            {
              key: 'copyJSON',
              value: function() {
                if (this.editjson_holder) {
                  var t = document.createElement('textarea');
                  (t.value = this.editjson_textarea.value),
                    t.setAttribute('readonly', ''),
                    (t.style.position = 'absolute'),
                    (t.style.left = '-9999px'),
                    document.body.appendChild(t),
                    t.select(),
                    document.execCommand('copy'),
                    document.body.removeChild(t);
                }
              },
            },
            {
              key: 'saveJSON',
              value: function() {
                if (this.editjson_holder)
                  try {
                    var t = JSON.parse(this.editjson_textarea.value);
                    this.setValue(t), this.hideEditJSON(), this.onChange(!0);
                  } catch (t) {
                    throw (window.alert('invalid JSON'), t);
                  }
              },
            },
            {
              key: 'toggleEditJSON',
              value: function() {
                this.editing_json ? this.hideEditJSON() : this.showEditJSON();
              },
            },
            {
              key: 'insertPropertyControlUsingPropertyOrder',
              value: function(t, e, r) {
                var n;
                this.schema.properties[t] && (n = this.schema.properties[t].propertyOrder), 'number' != typeof n && (n = 1e3), (e.propertyOrder = n);
                for (var i = 0; i < r.childNodes.length; i++) {
                  var o = r.childNodes[i];
                  if (e.propertyOrder < o.propertyOrder) {
                    this.addproperty_list.insertBefore(e, o), (e = null);
                    break;
                  }
                }
                e && this.addproperty_list.appendChild(e);
              },
            },
            {
              key: 'addPropertyCheckbox',
              value: function(t) {
                var e,
                  r = this,
                  n = this.theme.getCheckbox();
                (n.style.width = 'auto'), (e = this.schema.properties[t] && this.schema.properties[t].title ? this.schema.properties[t].title : t);
                var i = this.theme.getCheckboxLabel(e),
                  o = this.theme.getFormControl(i, n);
                return (
                  (o.style.paddingBottom = o.style.marginBottom = o.style.paddingTop = o.style.marginTop = 0),
                  (o.style.height = 'auto'),
                  this.insertPropertyControlUsingPropertyOrder(t, o, this.addproperty_list),
                  (n.checked = t in this.editors),
                  n.addEventListener('change', function() {
                    n.checked ? r.addObjectProperty(t) : r.removeObjectProperty(t), r.onChange(!0);
                  }),
                  (this.addproperty_checkboxes[t] = n),
                  n
                );
              },
            },
            {
              key: 'showAddProperty',
              value: function() {
                this.addproperty_holder &&
                  (this.hideEditJSON(),
                  (this.addproperty_holder.style.left = ''.concat(this.addproperty_button.offsetLeft, 'px')),
                  (this.addproperty_holder.style.top = ''.concat(this.addproperty_button.offsetTop + this.addproperty_button.offsetHeight, 'px')),
                  this.disable(),
                  (this.adding_property = !0),
                  (this.addproperty_button.disabled = !1),
                  (this.addproperty_holder.style.display = ''),
                  this.refreshAddProperties());
              },
            },
            {
              key: 'hideAddProperty',
              value: function() {
                this.addproperty_holder && this.adding_property && ((this.addproperty_holder.style.display = 'none'), this.enable(), (this.adding_property = !1));
              },
            },
            {
              key: 'toggleAddProperty',
              value: function() {
                this.adding_property ? this.hideAddProperty() : this.showAddProperty();
              },
            },
            {
              key: 'removeObjectProperty',
              value: function(t) {
                this.editors[t] && (this.editors[t].unregister(), delete this.editors[t], this.refreshValue(), this.layoutEditors());
              },
            },
            {
              key: 'getSchemaOnMaxDepth',
              value: function(t) {
                return Object.keys(t).reduce(function(e, r) {
                  switch (r) {
                    case '$ref':
                      return e;
                    case 'properties':
                    case 'items':
                      return ie(ie({}, e), {}, oe({}, r, {}));
                    case 'additionalProperties':
                    case 'propertyNames':
                      return ie(ie({}, e), {}, oe({}, r, !0));
                    default:
                      return ie(ie({}, e), {}, oe({}, r, t[r]));
                  }
                }, {});
              },
            },
            {
              key: 'addObjectProperty',
              value: function(t, e) {
                if (!this.editors[t]) {
                  if (this.cached_editors[t]) {
                    if (((this.editors[t] = this.cached_editors[t]), e)) return;
                    this.editors[t].register();
                  } else {
                    if (
                      !(
                        this.canHaveAdditionalProperties() ||
                        (this.schema.properties && this.schema.properties[t]) ||
                        (this.schema.patternProperties &&
                          Object.keys(this.schema.patternProperties).find(function(e) {
                            return new RegExp(e).test(t);
                          }))
                      )
                    )
                      return;
                    var r = this.getPropertySchema(t);
                    'number' != typeof r.propertyOrder && (r.propertyOrder = Object.keys(this.editors).length + 1e3);
                    var n = this.jsoneditor.getEditorClass(r),
                      i = this.jsoneditor.options.max_depth;
                    if (
                      ((this.editors[t] = this.jsoneditor.createEditor(
                        n,
                        {
                          jsoneditor: this.jsoneditor,
                          schema: i && this.currentDepth >= i ? this.getSchemaOnMaxDepth(r) : r,
                          path: ''.concat(this.path, '.').concat(t),
                          template_path: this.getTemplatePathForChild(t),
                          parent: this,
                        },
                        this.currentDepth + 1
                      )),
                      this.editors[t].preBuild(),
                      !e)
                    ) {
                      var o = this.theme.getChildEditorHolder();
                      this.editor_holder.appendChild(o),
                        this.editors[t].setContainer(o),
                        this.editors[t].build(),
                        this.editors[t].postBuild(),
                        this.editors[t].setOptInCheckbox(n.header),
                        this.editors[t].activate();
                    }
                    this.cached_editors[t] = this.editors[t];
                  }
                  e || (this.refreshValue(), this.layoutEditors());
                }
              },
            },
            {
              key: 'onOutsideModalClick',
              value: function(t) {
                var e = t.path || (t.composedPath && t.composedPath());
                this.addproperty_holder && !this.addproperty_holder.contains(e[0]) && this.adding_property && (t.preventDefault(), t.stopPropagation(), this.toggleAddProperty());
              },
            },
            {
              key: 'onChildEditorChange',
              value: function(t) {
                this.refreshValue(), ue(fe(o.prototype), 'onChildEditorChange', this).call(this, t);
              },
            },
            {
              key: 'canHaveAdditionalProperties',
              value: function() {
                return 'boolean' == typeof this.schema.additionalProperties ? this.schema.additionalProperties : !this.jsoneditor.options.no_additional_properties;
              },
            },
            {
              key: 'destroy',
              value: function() {
                Object.values(this.cached_editors).forEach(function(t) {
                  return t.destroy();
                }),
                  this.editor_holder && (this.editor_holder.innerHTML = ''),
                  this.title && this.title.parentNode && this.title.parentNode.removeChild(this.title),
                  this.error_holder && this.error_holder.parentNode && this.error_holder.parentNode.removeChild(this.error_holder),
                  (this.editors = null),
                  (this.cached_editors = null),
                  this.editor_holder && this.editor_holder.parentNode && this.editor_holder.parentNode.removeChild(this.editor_holder),
                  (this.editor_holder = null),
                  document.removeEventListener('click', this.onOutsideModalClick),
                  ue(fe(o.prototype), 'destroy', this).call(this);
              },
            },
            {
              key: 'getValue',
              value: function() {
                if (this.dependenciesFulfilled) {
                  var t = ue(fe(o.prototype), 'getValue', this).call(this);
                  return (
                    t &&
                      (this.jsoneditor.options.remove_empty_properties || this.options.remove_empty_properties) &&
                      Object.keys(t).forEach(function(e) {
                        var r;
                        (void 0 === (r = t[e]) || '' === r || (r === Object(r) && 0 === Object.keys(r).length && r.constructor === Object)) && delete t[e];
                      }),
                    t
                  );
                }
              },
            },
            {
              key: 'refreshValue',
              value: function() {
                var t = this;
                (this.value = {}),
                  this.editors &&
                    (Object.keys(this.editors).forEach(function(e) {
                      t.editors[e].isActive() && (t.value[e] = t.editors[e].getValue());
                    }),
                    this.adding_property && this.refreshAddProperties());
              },
            },
            {
              key: 'refreshAddProperties',
              value: function() {
                var t = this;
                if (this.options.disable_properties || (!1 !== this.options.disable_properties && this.jsoneditor.options.disable_properties)) this.addproperty_button.style.display = 'none';
                else {
                  var e,
                    r = 0,
                    n = !1;
                  Object.keys(this.editors).forEach(function(t) {
                    return r++;
                  }),
                    (e = this.canHaveAdditionalProperties() && !(void 0 !== this.schema.maxProperties && r >= this.schema.maxProperties)),
                    this.addproperty_checkboxes && (this.addproperty_list.innerHTML = ''),
                    (this.addproperty_checkboxes = {}),
                    Object.keys(this.cached_editors).forEach(function(i) {
                      t.addPropertyCheckbox(i),
                        t.isRequiredObject(t.cached_editors[i]) && i in t.editors && (t.addproperty_checkboxes[i].disabled = !0),
                        void 0 !== t.schema.minProperties && r <= t.schema.minProperties
                          ? ((t.addproperty_checkboxes[i].disabled = t.addproperty_checkboxes[i].checked), t.addproperty_checkboxes[i].checked || (n = !0))
                          : i in t.editors
                          ? (n = !0)
                          : e || v(t.schema.properties, i)
                          ? ((t.addproperty_checkboxes[i].disabled = !1), (n = !0))
                          : (t.addproperty_checkboxes[i].disabled = !0);
                    }),
                    this.canHaveAdditionalProperties() && (n = !0),
                    Object.keys(this.schema.properties).forEach(function(e) {
                      t.cached_editors[e] || ((n = !0), t.addPropertyCheckbox(e));
                    }),
                    n
                      ? this.canHaveAdditionalProperties()
                        ? (this.addproperty_add.disabled = !e)
                        : ((this.addproperty_add.style.display = 'none'), (this.addproperty_input.style.display = 'none'))
                      : (this.hideAddProperty(), (this.addproperty_button.style.display = 'none'));
                }
              },
            },
            {
              key: 'isRequiredObject',
              value: function(t) {
                if (t)
                  return 'boolean' == typeof t.schema.required
                    ? t.schema.required
                    : Array.isArray(this.schema.required)
                    ? this.schema.required.includes(t.key)
                    : !!this.jsoneditor.options.required_by_default;
              },
            },
            {
              key: 'setValue',
              value: function(t, e) {
                var r = this;
                ('object' !== le((t = t || {})) || Array.isArray(t)) && (t = {}),
                  Object.entries(this.cached_editors).forEach(function(n) {
                    var i = ae(n, 2),
                      o = i[0],
                      a = i[1];
                    void 0 !== t[o]
                      ? (r.addObjectProperty(o), a.setValue(t[o], e), a.activate())
                      : e || r.isRequiredObject(a)
                      ? a.setValue(a.getDefault(), e)
                      : r.jsoneditor.options.show_opt_in || r.options.show_opt_in
                      ? a.deactivate()
                      : r.removeObjectProperty(o);
                  }),
                  Object.entries(t).forEach(function(t) {
                    var n = ae(t, 2),
                      i = n[0],
                      o = n[1];
                    r.cached_editors[i] || (r.addObjectProperty(i), r.editors[i] && r.editors[i].setValue(o, e, !!r.editors[i].template));
                  }),
                  this.refreshValue(),
                  this.layoutEditors(),
                  this.onChange();
              },
            },
            {
              key: 'showValidationErrors',
              value: function(t) {
                var e = this,
                  r = [],
                  n = [];
                t.forEach(function(t) {
                  t.path === e.path ? r.push(t) : n.push(t);
                }),
                  this.error_holder &&
                    (r.length
                      ? ((this.error_holder.innerHTML = ''),
                        (this.error_holder.style.display = ''),
                        r.forEach(function(t) {
                          t.errorcount && t.errorcount > 1 && (t.message += ' ('.concat(t.errorcount, ' errors)')), e.error_holder.appendChild(e.theme.getErrorMessage(t.message));
                        }))
                      : (this.error_holder.style.display = 'none')),
                  this.options.table_row && (r.length ? this.theme.addTableRowError(this.container) : this.theme.removeTableRowError(this.container)),
                  Object.values(this.editors).forEach(function(t) {
                    t.showValidationErrors(n);
                  });
              },
            },
          ]) && ce(e.prototype, r),
          n && ce(e, n),
          o
        );
      })(M);
      ye.rules = {
        '.je-object__title': 'display:inline-block',
        '.je-object__controls': 'margin:0%200%200%2010px',
        '.je-object__container': 'position:relative',
        '.je-object__property-checkbox': 'margin:0;height:auto',
        '.property-selector': 'width:295px;max-height:160px;padding:5px%200;overflow-y:auto;overflow-x:hidden;padding-left:5px',
        '.property-selector-input': 'width:220px;margin-bottom:0;display:inline-block',
        '.json-editor-btntype-toggle': 'margin:0%2010px%200%200',
        '.je-edit-json--textarea': 'height:170px;width:300px;display:block',
      };
      r(158);
      function me(t) {
        return (me =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function ve(t, e) {
        if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
      }
      function be(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      function ge(t, e, r) {
        return (ge =
          'undefined' != typeof Reflect && Reflect.get
            ? Reflect.get
            : function(t, e, r) {
                var n = (function(t, e) {
                  for (; !Object.prototype.hasOwnProperty.call(t, e) && null !== (t = xe(t)); );
                  return t;
                })(t, e);
                if (n) {
                  var i = Object.getOwnPropertyDescriptor(n, e);
                  return i.get ? i.get.call(r) : i.value;
                }
              })(t, e, r || t);
      }
      function _e(t, e) {
        return (_e =
          Object.setPrototypeOf ||
          function(t, e) {
            return (t.__proto__ = e), t;
          })(t, e);
      }
      function we(t) {
        var e = (function() {
          if ('undefined' == typeof Reflect || !Reflect.construct) return !1;
          if (Reflect.construct.sham) return !1;
          if ('function' == typeof Proxy) return !0;
          try {
            return Boolean.prototype.valueOf.call(Reflect.construct(Boolean, [], function() {})), !0;
          } catch (t) {
            return !1;
          }
        })();
        return function() {
          var r,
            n = xe(t);
          if (e) {
            var i = xe(this).constructor;
            r = Reflect.construct(n, arguments, i);
          } else r = n.apply(this, arguments);
          return ke(this, r);
        };
      }
      function ke(t, e) {
        return !e || ('object' !== me(e) && 'function' != typeof e)
          ? (function(t) {
              if (void 0 === t) throw new ReferenceError("this hasn't been initialised - super() hasn't been called");
              return t;
            })(t)
          : e;
      }
      function xe(t) {
        return (xe = Object.setPrototypeOf
          ? Object.getPrototypeOf
          : function(t) {
              return t.__proto__ || Object.getPrototypeOf(t);
            })(t);
      }
      var je = {
        array: Y,
        button: nt,
        checkbox: dt,
        hidden: wt,
        integer: Gt,
        multiple: re,
        number: Ft,
        object: ye,
        string: Pt,
        table: (function(t) {
          !(function(t, e) {
            if ('function' != typeof e && null !== e) throw new TypeError('Super expression must either be null or a function');
            (t.prototype = Object.create(e && e.prototype, { constructor: { value: t, writable: !0, configurable: !0 } })), e && _e(t, e);
          })(o, t);
          var e,
            r,
            n,
            i = we(o);
          function o() {
            return ve(this, o), i.apply(this, arguments);
          }
          return (
            (e = o),
            (r = [
              {
                key: 'register',
                value: function() {
                  if ((ge(xe(o.prototype), 'register', this).call(this), this.rows)) for (var t = 0; t < this.rows.length; t++) this.rows[t].register();
                },
              },
              {
                key: 'unregister',
                value: function() {
                  if ((ge(xe(o.prototype), 'unregister', this).call(this), this.rows)) for (var t = 0; t < this.rows.length; t++) this.rows[t].unregister();
                },
              },
              {
                key: 'getNumColumns',
                value: function() {
                  return Math.max(Math.min(12, this.width), 3);
                },
              },
              {
                key: 'preBuild',
                value: function() {
                  var t = this.jsoneditor.expandRefs(this.schema.items || {});
                  (this.item_title = t.title || 'row'),
                    (this.item_default = t.default || null),
                    (this.item_has_child_editors = t.properties || t.items),
                    (this.width = 12),
                    (this.array_controls_top = this.options.array_controls_top || this.jsoneditor.options.array_controls_top),
                    ge(xe(o.prototype), 'preBuild', this).call(this);
                },
              },
              {
                key: 'build',
                value: function() {
                  (this.table = this.theme.getTable()),
                    this.container.appendChild(this.table),
                    (this.thead = this.theme.getTableHead()),
                    this.table.appendChild(this.thead),
                    (this.header_row = this.theme.getTableRow()),
                    this.thead.appendChild(this.header_row),
                    (this.row_holder = this.theme.getTableBody()),
                    this.table.appendChild(this.row_holder);
                  var t = this.getElementEditor(0, !0);
                  if (((this.item_default = t.getDefault()), (this.width = t.getNumColumns() + 2), this.options.compact))
                    (this.panel = document.createElement('div')), this.container.appendChild(this.panel);
                  else {
                    (this.header = document.createElement('label')), (this.header.textContent = this.getTitle());
                    var e = document.createElement('span');
                    e.classList.add('je-array-subheader'),
                      (e.innerText = '( loop )'),
                      this.header.appendChild(e),
                      (this.title = this.theme.getHeader(this.header, this.getPathDepth())),
                      this.container.appendChild(this.title),
                      this.options.infoText && ((this.infoButton = this.theme.getInfoButton(this.translateProperty(this.options.infoText))), this.container.appendChild(this.infoButton)),
                      (this.title_controls = this.theme.getHeaderButtonHolder()),
                      this.title.appendChild(this.title_controls),
                      this.schema.description && ((this.description = this.theme.getDescription(this.translateProperty(this.schema.description))), this.container.appendChild(this.description)),
                      (this.panel = this.theme.getIndentedPanel('table')),
                      this.container.appendChild(this.panel),
                      (this.error_holder = document.createElement('div')),
                      this.panel.appendChild(this.error_holder);
                  }
                  if (
                    (this.panel.appendChild(this.table),
                    (this.controls = this.theme.getButtonHolder()),
                    this.array_controls_top ? this.title.appendChild(this.controls) : this.panel.appendChild(this.controls),
                    (this.controls_header_cell = this.theme.getTableHeaderCell(' ')),
                    this.controls_header_cell.setAttribute('aria-hidden', 'true'),
                    this.header_row.appendChild(this.controls_header_cell),
                    this.item_has_child_editors)
                  )
                    for (var r = t.getChildEditors(), n = t.property_order || Object.keys(r), i = 0; i < n.length; i++) {
                      var o = this.theme.getTableHeaderCell(r[n[i]].getTitle());
                      r[n[i]].options.hidden && (o.style.display = 'none'), this.header_row.appendChild(o);
                    }
                  else this.header_row.appendChild(this.theme.getTableHeaderCell(this.item_title));
                  t.destroy(), (this.row_holder.innerHTML = ''), this.addControls();
                },
              },
              {
                key: 'onChildEditorChange',
                value: function(t) {
                  this.refreshValue(), ge(xe(o.prototype), 'onChildEditorChange', this).call(this);
                },
              },
              {
                key: 'getItemDefault',
                value: function() {
                  return f({}, { default: this.item_default }).default;
                },
              },
              {
                key: 'getItemTitle',
                value: function() {
                  return this.item_title;
                },
              },
              {
                key: 'getElementEditor',
                value: function(t, e) {
                  var r = f({}, this.schema.items),
                    n = this.jsoneditor.getEditorClass(r, this.jsoneditor),
                    i = this.row_holder.appendChild(this.theme.getTableRow()),
                    o = i,
                    a = null;
                  e || (a = i.appendChild(this.theme.getTableCell())).classList.add('je-table-controls-cell'), this.item_has_child_editors || ((o = this.theme.getTableCell()), i.appendChild(o));
                  var s = this.jsoneditor.createEditor(n, {
                    jsoneditor: this.jsoneditor,
                    schema: r,
                    container: o,
                    path: ''.concat(this.path, '.').concat(t),
                    template_path: ''.concat(this.template_path, ':'),
                    parent: this,
                    compact: !0,
                    table_row: !0,
                  });
                  return (
                    s.preBuild(),
                    e ||
                      (s.build(),
                      s.postBuild(),
                      (s.controls_cell = a),
                      (s.row = i),
                      (s.table_controls = this.theme.getButtonHolder()),
                      s.controls_cell.appendChild(s.table_controls),
                      (s.table_controls.style.margin = 0),
                      (s.table_controls.style.padding = 0)),
                    s
                  );
                },
              },
              {
                key: 'destroy',
                value: function() {
                  (this.innerHTML = ''),
                    this.checkParent(this.title) && this.title.parentNode.removeChild(this.title),
                    this.checkParent(this.description) && this.description.parentNode.removeChild(this.description),
                    this.checkParent(this.row_holder) && this.row_holder.parentNode.removeChild(this.row_holder),
                    this.checkParent(this.table) && this.table.parentNode.removeChild(this.table),
                    this.checkParent(this.panel) && this.panel.parentNode.removeChild(this.panel),
                    (this.rows = this.title = this.description = this.row_holder = this.table = this.panel = null),
                    ge(xe(o.prototype), 'destroy', this).call(this);
                },
              },
              {
                key: 'ensureArraySize',
                value: function(t) {
                  if ((Array.isArray(t) || (t = [t]), this.schema.minItems)) for (; t.length < this.schema.minItems; ) t.push(this.getItemDefault());
                  return this.schema.maxItems && t.length > this.schema.maxItems && (t = t.slice(0, this.schema.maxItems)), t;
                },
              },
              {
                key: 'setValue',
                value: function() {
                  var t = this,
                    e = arguments.length > 0 && void 0 !== arguments[0] ? arguments[0] : [],
                    r = arguments.length > 1 ? arguments[1] : void 0;
                  e = this.ensureArraySize(e);
                  var n = JSON.stringify(e);
                  if (n !== this.serialized) {
                    var i = !1;
                    e.forEach(function(e, r) {
                      t.rows[r] ? t.rows[r].setValue(e) : (t.addRow(e), (i = !0));
                    });
                    for (var o = e.length; o < this.rows.length; o++) {
                      var a = this.rows[o].container;
                      this.item_has_child_editors || this.rows[o].row.parentNode.removeChild(this.rows[o].row),
                        this.rows[o].destroy(),
                        a.parentNode && a.parentNode.removeChild(a),
                        (this.rows[o] = null),
                        (i = !0);
                    }
                    (this.rows = this.rows.slice(0, e.length)), this.refreshValue(), (i || r) && this.refreshRowButtons(), this.onChange();
                  }
                },
              },
              {
                key: 'refreshRowButtons',
                value: function() {
                  var t = this,
                    e = this.schema.minItems && this.schema.minItems >= this.rows.length,
                    r = this.schema.maxItems && this.schema.maxItems <= this.rows.length,
                    n = [];
                  this.rows.forEach(function(i, o) {
                    if (i.delete_button) {
                      var a = !e;
                      t.setVisibility(i.delete_button, a), n.push(a);
                    }
                    if (i.copy_button) {
                      var s = !r;
                      t.setVisibility(i.copy_button, s), n.push(s);
                    }
                    if (i.moveup_button) {
                      var l = 0 !== o;
                      t.setVisibility(i.moveup_button, l), n.push(l);
                    }
                    if (i.movedown_button) {
                      var c = o !== t.rows.length - 1;
                      t.setVisibility(i.movedown_button, c), n.push(c);
                    }
                  });
                  var i = n.some(function(t) {
                    return t;
                  });
                  this.rows.forEach(function(e) {
                    return t.setVisibility(e.controls_cell, i);
                  }),
                    this.setVisibility(this.controls_header_cell, i),
                    this.setVisibility(this.table, this.value.length);
                  var o = !(r || this.hide_add_button);
                  this.setVisibility(this.add_row_button, o);
                  var a = !(!this.value.length || e || this.hide_delete_last_row_buttons);
                  this.setVisibility(this.delete_last_row_button, a);
                  var s = !(this.value.length <= 1 || e || this.hide_delete_all_rows_buttons);
                  this.setVisibility(this.remove_all_rows_button, s);
                  var l = o || a || s;
                  this.setVisibility(this.controls, l);
                },
              },
              {
                key: 'refreshValue',
                value: function() {
                  var t = this;
                  (this.value = []),
                    this.rows.forEach(function(e, r) {
                      t.value[r] = e.getValue();
                    }),
                    (this.serialized = JSON.stringify(this.value));
                },
              },
              {
                key: 'addRow',
                value: function(t) {
                  var e = this.rows.length;
                  this.rows[e] = this.getElementEditor(e);
                  var r = this.rows[e].table_controls;
                  this.hide_delete_buttons || (this.rows[e].delete_button = this._createDeleteButton(e, r)),
                    this.show_copy_button && (this.rows[e].copy_button = this._createCopyButton(e, r)),
                    this.hide_move_buttons || (this.rows[e].moveup_button = this._createMoveUpButton(e, r)),
                    this.hide_move_buttons || (this.rows[e].movedown_button = this._createMoveDownButton(e, r)),
                    void 0 !== t && this.rows[e].setValue(t);
                },
              },
              {
                key: '_createDeleteButton',
                value: function(t, e) {
                  var r = this,
                    n = this.getButton('', 'delete', 'button_delete_row_title_short');
                  return (
                    n.classList.add('delete', 'json-editor-btntype-delete'),
                    n.setAttribute('data-i', t),
                    n.addEventListener('click', function(t) {
                      if ((t.preventDefault(), t.stopPropagation(), !r.askConfirmation())) return !1;
                      var e = 1 * t.currentTarget.getAttribute('data-i'),
                        n = r.getValue();
                      n.splice(e, 1), r.setValue(n), r.onChange(!0), r.jsoneditor.trigger('deleteRow', r.rows[e]);
                    }),
                    e.appendChild(n),
                    n
                  );
                },
              },
              {
                key: '_createCopyButton',
                value: function(t, e) {
                  var r = this,
                    n = this.getButton('', 'copy', 'button_copy_row_title_short');
                  return (
                    n.classList.add('copy', 'json-editor-btntype-copy'),
                    n.setAttribute('data-i', t),
                    n.addEventListener('click', function(t) {
                      t.preventDefault(), t.stopPropagation();
                      var e = 1 * t.currentTarget.getAttribute('data-i'),
                        n = r.getValue();
                      n.splice(e + 1, 0, n[e]), r.setValue(n), r.onChange(!0), r.jsoneditor.trigger('copyRow', r.rows[e + 1]);
                    }),
                    e.appendChild(n),
                    n
                  );
                },
              },
              {
                key: '_createMoveUpButton',
                value: function(t, e) {
                  var r = this,
                    n = this.getButton('', 'moveup', 'button_move_up_title');
                  return (
                    n.classList.add('moveup', 'json-editor-btntype-move'),
                    n.setAttribute('data-i', t),
                    n.addEventListener('click', function(t) {
                      t.preventDefault(), t.stopPropagation();
                      var e = 1 * t.currentTarget.getAttribute('data-i'),
                        n = r.getValue();
                      n.splice(e - 1, 0, n.splice(e, 1)[0]), r.setValue(n), r.onChange(!0), r.jsoneditor.trigger('moveRow', r.rows[e - 1]);
                    }),
                    e.appendChild(n),
                    n
                  );
                },
              },
              {
                key: '_createMoveDownButton',
                value: function(t, e) {
                  var r = this,
                    n = this.getButton('', 'movedown', 'button_move_down_title');
                  return (
                    n.classList.add('movedown', 'json-editor-btntype-move'),
                    n.setAttribute('data-i', t),
                    n.addEventListener('click', function(t) {
                      t.preventDefault(), t.stopPropagation();
                      var e = 1 * t.currentTarget.getAttribute('data-i'),
                        n = r.getValue();
                      n.splice(e + 1, 0, n.splice(e, 1)[0]), r.setValue(n), r.onChange(!0), r.jsoneditor.trigger('moveRow', r.rows[e + 1]);
                    }),
                    e.appendChild(n),
                    n
                  );
                },
              },
              {
                key: 'addControls',
                value: function() {
                  var t = this;
                  (this.collapsed = !1),
                    (this.toggle_button = this._createToggleButton()),
                    this.title_controls &&
                      (this.title.insertBefore(this.toggle_button, this.title.childNodes[0]),
                      this.toggle_button.addEventListener('click', function(e) {
                        e.preventDefault(),
                          e.stopPropagation(),
                          t.setVisibility(t.panel, t.collapsed),
                          t.collapsed
                            ? ((t.collapsed = !1), t.setButtonText(e.currentTarget, '', 'collapse', 'button_collapse'))
                            : ((t.collapsed = !0), t.setButtonText(e.currentTarget, '', 'expand', 'button_expand'));
                      }),
                      this.options.collapsed && y(this.toggle_button, 'click'),
                      this.schema.options && void 0 !== this.schema.options.disable_collapse
                        ? this.schema.options.disable_collapse && (this.toggle_button.style.display = 'none')
                        : this.jsoneditor.options.disable_collapse && (this.toggle_button.style.display = 'none')),
                    (this.add_row_button = this._createAddRowButton()),
                    (this.delete_last_row_button = this._createDeleteLastRowButton()),
                    (this.remove_all_rows_button = this._createRemoveAllRowsButton());
                },
              },
              {
                key: '_createToggleButton',
                value: function() {
                  var t = this.getButton('', 'collapse', 'button_collapse');
                  return t.classList.add('json-editor-btntype-toggle'), t;
                },
              },
              {
                key: '_createAddRowButton',
                value: function() {
                  var t = this,
                    e = this.getButton(this.getItemTitle(), 'add', 'button_add_row_title', [this.getItemTitle()]);
                  return (
                    e.classList.add('json-editor-btntype-add'),
                    e.addEventListener('click', function(e) {
                      e.preventDefault(), e.stopPropagation();
                      var r = t.addRow();
                      t.refreshValue(), t.refreshRowButtons(), t.onChange(!0), t.jsoneditor.trigger('addRow', r);
                    }),
                    this.controls.appendChild(e),
                    e
                  );
                },
              },
              {
                key: '_createDeleteLastRowButton',
                value: function() {
                  var t = this,
                    e = this.getButton('button_delete_last', 'subtract', 'button_delete_last_title', [this.getItemTitle()]);
                  return (
                    e.classList.add('json-editor-btntype-deletelast'),
                    e.addEventListener('click', function(e) {
                      if ((e.preventDefault(), e.stopPropagation(), !t.askConfirmation())) return !1;
                      var r = t.getValue(),
                        n = r.pop();
                      t.setValue(r), t.onChange(!0), t.jsoneditor.trigger('deleteRow', n);
                    }),
                    this.controls.appendChild(e),
                    e
                  );
                },
              },
              {
                key: '_createRemoveAllRowsButton',
                value: function() {
                  var t = this,
                    e = this.getButton('button_delete_all', 'delete', 'button_delete_all_title');
                  return (
                    e.classList.add('json-editor-btntype-deleteall'),
                    e.addEventListener('click', function(e) {
                      if ((e.preventDefault(), e.stopPropagation(), !t.askConfirmation())) return !1;
                      t.setValue([]), t.onChange(!0), t.jsoneditor.trigger('deleteAllRows');
                    }),
                    this.controls.appendChild(e),
                    e
                  );
                },
              },
            ]) && be(e.prototype, r),
            n && be(e, n),
            o
          );
        })(Y),
      };
      function Oe(t) {
        return (
          (function(t) {
            if (Array.isArray(t)) return Ee(t);
          })(t) ||
          (function(t) {
            if (('undefined' != typeof Symbol && null != t[Symbol.iterator]) || null != t['@@iterator']) return Array.from(t);
          })(t) ||
          (function(t, e) {
            if (!t) return;
            if ('string' == typeof t) return Ee(t, e);
            var r = Object.prototype.toString.call(t).slice(8, -1);
            'Object' === r && t.constructor && (r = t.constructor.name);
            if ('Map' === r || 'Set' === r) return Array.from(t);
            if ('Arguments' === r || /^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(r)) return Ee(t, e);
          })(t) ||
          (function() {
            throw new TypeError('Invalid attempt to spread non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.');
          })()
        );
      }
      function Ee(t, e) {
        (null == e || e > t.length) && (e = t.length);
        for (var r = 0, n = new Array(e); r < e; r++) n[r] = t[r];
        return n;
      }
      function Ce(t, e) {
        if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
      }
      function Se(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      var Ae = { collapse: '', expand: '', delete: '', edit: '', add: '', cancel: '', save: '', moveup: '', movedown: '' },
        Pe = (function() {
          function t() {
            var e = arguments.length > 0 && void 0 !== arguments[0] ? arguments[0] : '',
              r = arguments.length > 1 && void 0 !== arguments[1] ? arguments[1] : Ae;
            Ce(this, t), (this.mapping = r), (this.icon_prefix = e);
          }
          var e, r, n;
          return (
            (e = t),
            (r = [
              {
                key: 'getIconClass',
                value: function(t) {
                  return this.mapping[t] ? this.icon_prefix + this.mapping[t] : null;
                },
              },
              {
                key: 'getIcon',
                value: function(t) {
                  var e,
                    r = this.getIconClass(t);
                  if (!r) return null;
                  var n = document.createElement('i');
                  return (e = n.classList).add.apply(e, Oe(r.split(' '))), n;
                },
              },
            ]) && Se(e.prototype, r),
            n && Se(e, n),
            t
          );
        })();
      function Te(t) {
        return (Te =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function Re(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      function Ie(t, e) {
        return (Ie =
          Object.setPrototypeOf ||
          function(t, e) {
            return (t.__proto__ = e), t;
          })(t, e);
      }
      function Le(t) {
        var e = (function() {
          if ('undefined' == typeof Reflect || !Reflect.construct) return !1;
          if (Reflect.construct.sham) return !1;
          if ('function' == typeof Proxy) return !0;
          try {
            return Boolean.prototype.valueOf.call(Reflect.construct(Boolean, [], function() {})), !0;
          } catch (t) {
            return !1;
          }
        })();
        return function() {
          var r,
            n = Be(t);
          if (e) {
            var i = Be(this).constructor;
            r = Reflect.construct(n, arguments, i);
          } else r = n.apply(this, arguments);
          return Ne(this, r);
        };
      }
      function Ne(t, e) {
        return !e || ('object' !== Te(e) && 'function' != typeof e)
          ? (function(t) {
              if (void 0 === t) throw new ReferenceError("this hasn't been initialised - super() hasn't been called");
              return t;
            })(t)
          : e;
      }
      function Be(t) {
        return (Be = Object.setPrototypeOf
          ? Object.getPrototypeOf
          : function(t) {
              return t.__proto__ || Object.getPrototypeOf(t);
            })(t);
      }
      var Ve = {
          collapse: { sym: '#icon-chevron-down', vBox: '-5 -13 24 24', w: '24', h: '24' },
          expand: { sym: '#icon-chevron-right', vBox: '-5 -13 24 24', w: '24', h: '24' },
          edit: { sym: '#icon-pencil', vBox: '0 0 21 21', w: '15', h: '15' },
          delete: { sym: '#icon-trash', vBox: '0 0 13 14', w: '13', h: '14' },
          add: { sym: '#icon-plus', vBox: '0 0 10 10', w: '10', h: '10' },
          expandinput: { sym: '#icon-expand-input', vBox: '0 0 12 12', w: '14', h: '14' },
          collapseinput: { sym: '#icon-collapse-input', vBox: '0 0 14 14', w: '14', h: '14' },
          copy: { sym: '#icon-copy-clipboard', vBox: '0 0 20 20', w: '20', h: '20' },
        },
        De = {
          pdftron: (function(t) {
            !(function(t, e) {
              if ('function' != typeof e && null !== e) throw new TypeError('Super expression must either be null or a function');
              (t.prototype = Object.create(e && e.prototype, { constructor: { value: t, writable: !0, configurable: !0 } })), e && Ie(t, e);
            })(o, t);
            var e,
              r,
              n,
              i = Le(o);
            function o() {
              return (
                (function(t, e) {
                  if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
                })(this, o),
                i.call(this, '', [])
              );
            }
            return (
              (e = o),
              (r = [
                {
                  key: 'getIcon',
                  value: function(t) {
                    if (!Ve[t]) return null;
                    var e = Ve[t],
                      r = 'http://www.w3.org/2000/svg',
                      n = document.createElementNS(r, 'svg');
                    n.setAttributeNS(null, 'viewBox', e.vBox), n.setAttributeNS(null, 'width', e.w), n.setAttributeNS(null, 'height', e.h);
                    var i = document.createElementNS(r, 'use');
                    return n.appendChild(i), i.setAttributeNS(null, 'href', e.sym), n;
                  },
                },
              ]) && Re(e.prototype, r),
              n && Re(e, n),
              o
            );
          })(Pe),
        };
      r(159);
      function Fe(t, e) {
        if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
      }
      function Me(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      var He = ['matches', 'webkitMatchesSelector', 'mozMatchesSelector', 'msMatchesSelector', 'oMatchesSelector'].find(function(t) {
          return t in document.documentElement;
        }),
        qe = (function() {
          function t(e) {
            var r = arguments.length > 1 && void 0 !== arguments[1] ? arguments[1] : { disable_theme_rules: !1 };
            Fe(this, t),
              (this.jsoneditor = e),
              Object.keys(r).forEach(function(t) {
                void 0 !== e.options[t] && (r[t] = e.options[t]);
              }),
              (this.options = r);
          }
          var e, r, n;
          return (
            (e = t),
            (r = [
              {
                key: 'getContainer',
                value: function() {
                  return document.createElement('div');
                },
              },
              {
                key: 'getFloatRightLinkHolder',
                value: function() {
                  var t = document.createElement('div');
                  return t.classList.add('je-float-right-linkholder'), t;
                },
              },
              {
                key: 'getModal',
                value: function() {
                  var t = document.createElement('div');
                  return (t.style.display = 'none'), t.classList.add('je-modal'), t;
                },
              },
              {
                key: 'getGridContainer',
                value: function() {
                  return document.createElement('div');
                },
              },
              {
                key: 'getGridRow',
                value: function() {
                  var t = document.createElement('div');
                  return t.classList.add('row'), t;
                },
              },
              {
                key: 'getGridColumn',
                value: function() {
                  return document.createElement('div');
                },
              },
              { key: 'setGridColumnSize', value: function(t, e) {} },
              {
                key: 'getLink',
                value: function(t) {
                  var e = document.createElement('a');
                  return e.setAttribute('href', '#'), e.appendChild(document.createTextNode(t)), e;
                },
              },
              {
                key: 'disableHeader',
                value: function(t) {
                  t.style.color = '#ccc';
                },
              },
              {
                key: 'disableLabel',
                value: function(t) {
                  t.style.color = '#ccc';
                },
              },
              {
                key: 'enableHeader',
                value: function(t) {
                  t.style.color = '';
                },
              },
              {
                key: 'enableLabel',
                value: function(t) {
                  t.style.color = '';
                },
              },
              {
                key: 'getInfoButton',
                value: function(t) {
                  var e = document.createElement('span');
                  (e.innerText = 'ⓘ'), e.classList.add('je-infobutton-icon');
                  var r = document.createElement('span');
                  return (
                    r.classList.add('je-infobutton-tooltip'),
                    (r.innerText = t),
                    (e.onmouseover = function() {
                      r.style.visibility = 'visible';
                    }),
                    (e.onmouseleave = function() {
                      r.style.visibility = 'hidden';
                    }),
                    e.appendChild(r),
                    e
                  );
                },
              },
              {
                key: 'getFormInputLabel',
                value: function(t, e) {
                  var r = document.createElement('label');
                  return r.appendChild(document.createTextNode(t)), e && r.classList.add('required'), r;
                },
              },
              {
                key: 'getHeader',
                value: function(t, e) {
                  var r = document.createElement('h3');
                  return 'string' == typeof t ? (r.textContent = t) : r.appendChild(t), r.classList.add('je-header'), r;
                },
              },
              {
                key: 'getCheckbox',
                value: function() {
                  var t = this.getFormInputField('checkbox');
                  return t.classList.add('je-checkbox'), t;
                },
              },
              {
                key: 'getCheckboxLabel',
                value: function(t, e) {
                  var r = document.createElement('label');
                  return r.appendChild(document.createTextNode(' '.concat(t))), e && r.classList.add('required'), r;
                },
              },
              {
                key: 'getMultiCheckboxHolder',
                value: function(t, e, r, n) {
                  var i = document.createElement('div');
                  return (
                    i.classList.add('control-group'),
                    e && ((e.style.display = 'block'), i.appendChild(e), n && e.appendChild(n)),
                    Object.values(t).forEach(function(t) {
                      (t.style.display = 'inline-block'), (t.style.marginRight = '20px'), i.appendChild(t);
                    }),
                    r && i.appendChild(r),
                    i
                  );
                },
              },
              {
                key: 'getFormCheckboxControl',
                value: function(t, e, r) {
                  var n = document.createElement('div');
                  return n.appendChild(t), (e.style.width = 'auto'), t.insertBefore(e, t.firstChild), r && n.classList.add('je-checkbox-control--compact'), n;
                },
              },
              {
                key: 'getFormRadio',
                value: function(t) {
                  var e = this.getFormInputField('radio');
                  return (
                    Object.keys(t).forEach(function(r) {
                      return e.setAttribute(r, t[r]);
                    }),
                    e.classList.add('je-radio'),
                    e
                  );
                },
              },
              {
                key: 'getFormRadioLabel',
                value: function(t, e) {
                  var r = document.createElement('label');
                  return r.appendChild(document.createTextNode(' '.concat(t))), e && r.classList.add('required'), r;
                },
              },
              {
                key: 'getFormRadioControl',
                value: function(t, e, r) {
                  var n = document.createElement('div');
                  return n.appendChild(t), (e.style.width = 'auto'), t.insertBefore(e, t.firstChild), r && n.classList.add('je-radio-control--compact'), n;
                },
              },
              {
                key: 'getSelectInput',
                value: function(t, e) {
                  var r = document.createElement('select');
                  return t && this.setSelectOptions(r, t), r;
                },
              },
              {
                key: 'getSwitcher',
                value: function(t) {
                  var e = this.getSelectInput(t, !1);
                  return e.classList.add('je-switcher'), e;
                },
              },
              {
                key: 'getSwitcherOptions',
                value: function(t) {
                  return t.getElementsByTagName('option');
                },
              },
              {
                key: 'setSwitcherOptions',
                value: function(t, e, r) {
                  this.setSelectOptions(t, e, r);
                },
              },
              {
                key: 'setSelectOptions',
                value: function(t, e) {
                  var r = arguments.length > 2 && void 0 !== arguments[2] ? arguments[2] : [];
                  t.innerHTML = '';
                  for (var n = 0; n < e.length; n++) {
                    var i = document.createElement('option');
                    i.setAttribute('value', e[n]), (i.textContent = r[n] || e[n]), t.appendChild(i);
                  }
                },
              },
              {
                key: 'getTextareaInput',
                value: function() {
                  var t = document.createElement('textarea');
                  return t.classList.add('je-textarea'), t;
                },
              },
              {
                key: 'getRangeInput',
                value: function(t, e, r) {
                  var n = this.getFormInputField('range');
                  return n.setAttribute('min', t), n.setAttribute('max', e), n.setAttribute('step', r), n;
                },
              },
              {
                key: 'getStepperButtons',
                value: function(t) {
                  var e = document.createElement('div'),
                    r = document.createElement('button');
                  r.setAttribute('type', 'button'), r.classList.add('stepper-down');
                  var n = document.createElement('button');
                  n.setAttribute('type', 'button'),
                    n.classList.add('stepper-up'),
                    t.getAttribute('readonly') && (r.setAttribute('disabled', !0), n.setAttribute('disabled', !0)),
                    (r.textContent = '-'),
                    (n.textContent = '+');
                  var i = function(t, e) {
                      (t.value = Number(e || t.value)), t.setAttribute('initialized', '1');
                    },
                    o = t.getAttribute('min'),
                    a = t.getAttribute('max');
                  return (
                    r.addEventListener('click', function() {
                      t.getAttribute('initialized') ? (o ? Number(t.value) > Number(o) && t.stepDown() : t.stepDown()) : i(t, o), y(t, 'change');
                    }),
                    n.addEventListener('click', function() {
                      t.getAttribute('initialized') ? (a ? Number(t.value) < Number(a) && t.stepUp() : t.stepUp()) : i(t, o), y(t, 'change');
                    }),
                    e.appendChild(r),
                    e.appendChild(n),
                    e
                  );
                },
              },
              {
                key: 'getRangeOutput',
                value: function(t, e) {
                  var r = document.createElement('output');
                  r.value = e || 0;
                  var n = function(t) {
                    r.value = t.currentTarget.value;
                  };
                  return t.addEventListener('change', n, !1), t.addEventListener('input', n, !1), r;
                },
              },
              {
                key: 'getRangeControl',
                value: function(t, e) {
                  var r = document.createElement('div');
                  return r.classList.add('je-range-control'), e && r.appendChild(e), r.appendChild(t), r;
                },
              },
              {
                key: 'getFormInputField',
                value: function(t) {
                  var e = document.createElement('input');
                  return e.setAttribute('type', t), e;
                },
              },
              { key: 'afterInputReady', value: function(t) {} },
              {
                key: 'getFormControl',
                value: function(t, e, r, n, i) {
                  var o = document.createElement('div');
                  return (
                    o.classList.add('form-control'),
                    t && (o.appendChild(t), i && t.setAttribute('for', i)),
                    ('checkbox' !== e.type && 'radio' !== e.type) || !t
                      ? (n && t && t.appendChild(n), o.appendChild(e))
                      : ((e.style.width = 'auto'), t.insertBefore(e, t.firstChild), n && t.appendChild(n)),
                    r && o.appendChild(r),
                    o
                  );
                },
              },
              {
                key: 'getIndentedPanel',
                value: function() {
                  var t = document.createElement('div');
                  return t.classList.add('je-indented-panel'), t;
                },
              },
              {
                key: 'getTopIndentedPanel',
                value: function() {
                  var t = document.createElement('div');
                  return t.classList.add('je-indented-panel--top'), t;
                },
              },
              {
                key: 'getChildEditorHolder',
                value: function() {
                  return document.createElement('div');
                },
              },
              {
                key: 'getDescription',
                value: function(t) {
                  var e = document.createElement('p');
                  return window.DOMPurify ? (e.innerHTML = window.DOMPurify.sanitize(t)) : (e.textContent = this.cleanText(t)), e;
                },
              },
              {
                key: 'getCheckboxDescription',
                value: function(t) {
                  return this.getDescription(t);
                },
              },
              {
                key: 'getFormInputDescription',
                value: function(t) {
                  return this.getDescription(t);
                },
              },
              {
                key: 'getButtonHolder',
                value: function() {
                  return document.createElement('span');
                },
              },
              {
                key: 'getHeaderButtonHolder',
                value: function() {
                  return this.getButtonHolder();
                },
              },
              {
                key: 'getFormButtonHolder',
                value: function(t) {
                  return this.getButtonHolder();
                },
              },
              {
                key: 'getButton',
                value: function(t, e, r) {
                  var n = document.createElement('button');
                  return (n.type = 'button'), this.setButtonText(n, t, e, r), n;
                },
              },
              {
                key: 'getFormButton',
                value: function(t, e, r) {
                  return this.getButton(t, e, r);
                },
              },
              {
                key: 'setButtonText',
                value: function(t, e, r, n) {
                  for (; t.firstChild; ) t.removeChild(t.firstChild);
                  if ((r && (t.appendChild(r), (e = ' '.concat(e))), !this.jsoneditor.options.iconlib || !this.jsoneditor.options.remove_button_labels || !r)) {
                    var i = document.createElement('span');
                    i.appendChild(document.createTextNode(e)), t.appendChild(i);
                  }
                  n && t.setAttribute('title', n);
                },
              },
              {
                key: 'getTable',
                value: function() {
                  return document.createElement('table');
                },
              },
              {
                key: 'getTableRow',
                value: function() {
                  return document.createElement('tr');
                },
              },
              {
                key: 'getTableHead',
                value: function() {
                  return document.createElement('thead');
                },
              },
              {
                key: 'getTableBody',
                value: function() {
                  return document.createElement('tbody');
                },
              },
              {
                key: 'getTableHeaderCell',
                value: function(t) {
                  var e = document.createElement('th');
                  return (e.textContent = t), e;
                },
              },
              {
                key: 'getTableCell',
                value: function() {
                  return document.createElement('td');
                },
              },
              {
                key: 'getErrorMessage',
                value: function(t) {
                  var e = document.createElement('p');
                  return (e.style = e.style || {}), (e.style.color = 'red'), e.appendChild(document.createTextNode(t)), e;
                },
              },
              { key: 'addInputError', value: function(t, e) {} },
              { key: 'removeInputError', value: function(t) {} },
              { key: 'addTableRowError', value: function(t) {} },
              { key: 'removeTableRowError', value: function(t) {} },
              {
                key: 'getTabHolder',
                value: function(t) {
                  var e = void 0 === t ? '' : t,
                    r = document.createElement('div');
                  return (r.innerHTML = "<div class='je-tabholder tabs'></div><div class='content' id='".concat(e, "'></div><div class='je-tabholder--clear'></div>")), r;
                },
              },
              {
                key: 'getTopTabHolder',
                value: function(t) {
                  var e = void 0 === t ? '' : t,
                    r = document.createElement('div');
                  return (r.innerHTML = "<div class='tabs je-tabholder--top'></div><div class='je-tabholder--clear'></div><div class='content' id='".concat(e, "'></div>")), r;
                },
              },
              {
                key: 'applyStyles',
                value: function(t, e) {
                  Object.keys(e).forEach(function(r) {
                    return (t.style[r] = e[r]);
                  });
                },
              },
              {
                key: 'closest',
                value: function(t, e) {
                  for (; t && t !== document; ) {
                    if (!t[He]) return !1;
                    if (t[He](e)) return t;
                    t = t.parentNode;
                  }
                  return !1;
                },
              },
              {
                key: 'insertBasicTopTab',
                value: function(t, e) {
                  e.firstChild.insertBefore(t, e.firstChild.firstChild);
                },
              },
              {
                key: 'getTab',
                value: function(t, e) {
                  var r = document.createElement('div');
                  return r.appendChild(t), (r.id = e), r.classList.add('je-tab'), r;
                },
              },
              {
                key: 'getTopTab',
                value: function(t, e) {
                  var r = document.createElement('div');
                  return r.appendChild(t), (r.id = e), r.classList.add('je-tab--top'), r;
                },
              },
              {
                key: 'getTabContentHolder',
                value: function(t) {
                  return t.children[1];
                },
              },
              {
                key: 'getTopTabContentHolder',
                value: function(t) {
                  return t.children[1];
                },
              },
              {
                key: 'getTabContent',
                value: function() {
                  return this.getIndentedPanel();
                },
              },
              {
                key: 'getTopTabContent',
                value: function() {
                  return this.getTopIndentedPanel();
                },
              },
              {
                key: 'markTabActive',
                value: function(t) {
                  this.applyStyles(t.tab, { opacity: 1, background: 'white' }), void 0 !== t.rowPane ? (t.rowPane.style.display = '') : (t.container.style.display = '');
                },
              },
              {
                key: 'markTabInactive',
                value: function(t) {
                  this.applyStyles(t.tab, { opacity: 0.5, background: '' }), void 0 !== t.rowPane ? (t.rowPane.style.display = 'none') : (t.container.style.display = 'none');
                },
              },
              {
                key: 'addTab',
                value: function(t, e) {
                  t.children[0].appendChild(e);
                },
              },
              {
                key: 'addTopTab',
                value: function(t, e) {
                  t.children[0].appendChild(e);
                },
              },
              {
                key: 'getBlockLink',
                value: function() {
                  var t = document.createElement('a');
                  return t.classList.add('je-block-link'), t;
                },
              },
              {
                key: 'getBlockLinkHolder',
                value: function() {
                  return document.createElement('div');
                },
              },
              {
                key: 'getLinksHolder',
                value: function() {
                  return document.createElement('div');
                },
              },
              {
                key: 'createMediaLink',
                value: function(t, e, r) {
                  t.appendChild(e), r.classList.add('je-media'), t.appendChild(r);
                },
              },
              {
                key: 'createImageLink',
                value: function(t, e, r) {
                  t.appendChild(e), e.appendChild(r);
                },
              },
              {
                key: 'getFirstTab',
                value: function(t) {
                  return t.firstChild.firstChild;
                },
              },
              { key: 'getInputGroup', value: function(t, e) {} },
              {
                key: 'cleanText',
                value: function(t) {
                  var e = document.createElement('div');
                  return (e.innerHTML = t), e.textContent || e.innerText;
                },
              },
              {
                key: 'getDropZone',
                value: function(t) {
                  var e = document.createElement('div');
                  return e.setAttribute('data-text', t), e.classList.add('je-dropzone'), e;
                },
              },
              {
                key: 'getUploadPreview',
                value: function(t, e, r) {
                  var n = document.createElement('div');
                  if ((n.classList.add('je-upload-preview'), 'image' === t.mimeType.substr(0, 5))) {
                    var i = document.createElement('img');
                    (i.src = r), n.appendChild(i);
                  }
                  var o = document.createElement('div');
                  (o.innerHTML += '<strong>Name:</strong> '
                    .concat(t.name, '<br><strong>Type:</strong> ')
                    .concat(t.type, '<br><strong>Size:</strong> ')
                    .concat(t.formattedSize)),
                    n.appendChild(o),
                    n.appendChild(e);
                  var a = document.createElement('div');
                  return (a.style.clear = 'left'), n.appendChild(a), n;
                },
              },
              {
                key: 'getProgressBar',
                value: function() {
                  var t = document.createElement('progress');
                  return t.setAttribute('max', 100), t.setAttribute('value', 0), t;
                },
              },
              {
                key: 'updateProgressBar',
                value: function(t, e) {
                  t && t.setAttribute('value', e);
                },
              },
              {
                key: 'updateProgressBarUnknown',
                value: function(t) {
                  t && t.removeAttribute('value');
                },
              },
            ]) && Me(e.prototype, r),
            n && Me(e, n),
            t
          );
        })();
      function Ue(t) {
        return (Ue =
          'function' == typeof Symbol && 'symbol' == typeof Symbol.iterator
            ? function(t) {
                return typeof t;
              }
            : function(t) {
                return t && 'function' == typeof Symbol && t.constructor === Symbol && t !== Symbol.prototype ? 'symbol' : typeof t;
              })(t);
      }
      function ze(t, e) {
        if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
      }
      function $e(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      function Je(t, e, r) {
        return (Je =
          'undefined' != typeof Reflect && Reflect.get
            ? Reflect.get
            : function(t, e, r) {
                var n = (function(t, e) {
                  for (; !Object.prototype.hasOwnProperty.call(t, e) && null !== (t = Xe(t)); );
                  return t;
                })(t, e);
                if (n) {
                  var i = Object.getOwnPropertyDescriptor(n, e);
                  return i.get ? i.get.call(r) : i.value;
                }
              })(t, e, r || t);
      }
      function Ge(t, e) {
        return (Ge =
          Object.setPrototypeOf ||
          function(t, e) {
            return (t.__proto__ = e), t;
          })(t, e);
      }
      function We(t) {
        var e = (function() {
          if ('undefined' == typeof Reflect || !Reflect.construct) return !1;
          if (Reflect.construct.sham) return !1;
          if ('function' == typeof Proxy) return !0;
          try {
            return Boolean.prototype.valueOf.call(Reflect.construct(Boolean, [], function() {})), !0;
          } catch (t) {
            return !1;
          }
        })();
        return function() {
          var r,
            n = Xe(t);
          if (e) {
            var i = Xe(this).constructor;
            r = Reflect.construct(n, arguments, i);
          } else r = n.apply(this, arguments);
          return Ye(this, r);
        };
      }
      function Ye(t, e) {
        return !e || ('object' !== Ue(e) && 'function' != typeof e)
          ? (function(t) {
              if (void 0 === t) throw new ReferenceError("this hasn't been initialised - super() hasn't been called");
              return t;
            })(t)
          : e;
      }
      function Xe(t) {
        return (Xe = Object.setPrototypeOf
          ? Object.getPrototypeOf
          : function(t) {
              return t.__proto__ || Object.getPrototypeOf(t);
            })(t);
      }
      var Ke = (function(t) {
        !(function(t, e) {
          if ('function' != typeof e && null !== e) throw new TypeError('Super expression must either be null or a function');
          (t.prototype = Object.create(e && e.prototype, { constructor: { value: t, writable: !0, configurable: !0 } })), e && Ge(t, e);
        })(o, t);
        var e,
          r,
          n,
          i = We(o);
        function o() {
          return ze(this, o), i.apply(this, arguments);
        }
        return (
          (e = o),
          (r = [
            {
              key: 'addInputError',
              value: function(t, e) {
                if (t.errmsg) t.errmsg.style.display = 'block';
                else {
                  var r = this.closest(t, '.form-control');
                  (t.errmsg = document.createElement('div')), t.errmsg.setAttribute('class', 'errmsg'), r.appendChild(t.errmsg);
                }
                (t.errmsg.innerHTML = ''), t.errmsg.appendChild(document.createTextNode(e));
              },
            },
            {
              key: 'removeInputError',
              value: function(t) {
                t.style && (t.style.borderColor = ''), t.errmsg && (t.errmsg.style.display = 'none');
              },
            },
            {
              key: 'getIndentedPanel',
              value: function(t) {
                var e = Je(Xe(o.prototype), 'getIndentedPanel', this).call(this, t);
                switch (t) {
                  case 'table':
                    e.classList.add('je-table-panel');
                }
                return e;
              },
            },
            {
              key: 'setButtonText',
              value: function(t, e, r, n) {
                for (; t.firstChild; ) t.removeChild(t.firstChild);
                if ((r && (t.appendChild(r), (e = ' '.concat(e))), !this.jsoneditor.options.iconlib || !this.jsoneditor.options.remove_button_labels || !r)) {
                  var i = document.createElement('span');
                  i.appendChild(document.createTextNode(e)), t.appendChild(i);
                }
                n && t.setAttribute('title', n);
              },
            },
          ]) && $e(e.prototype, r),
          n && $e(e, n),
          o
        );
      })(qe);
      Ke.rules = {
        '.je-upload-preview img': 'float:left;margin:0%200.5rem%200.5rem%200;max-width:100%25;max-height:5rem',
        '.je-dropzone': 'position:relative;margin:0.5rem%200;border:2px%20dashed%20black;width:100%25;height:60px;background:teal;transition:all%200.5s',
        '.je-dropzone:before': 'position:absolute;content:attr(data-text);color:rgba(0%2C%200%2C%200%2C%200.6);left:50%25;top:50%25;transform:translate(-50%25%2C%20-50%25)',
        '.je-dropzone.valid-dropzone': 'background:green',
        '.je-dropzone.invalid-dropzone': 'background:red',
      };
      var Ze = { pdftron: Ke },
        Qe = {
          '.je-float-right-linkholder': 'float:right;margin-left:10px',
          '.je-modal': 'background-color:white;border:1px%20solid%20black;box-shadow:3px%203px%20black;position:absolute;z-index:10',
          '.je-infobutton-icon': 'font-size:16px;font-weight:bold;padding:0.25rem;position:relative;display:inline-block',
          '.je-infobutton-tooltip':
            'font-size:12px;font-weight:normal;font-family:sans-serif;visibility:hidden;background-color:rgba(50%2C%2050%2C%2050%2C%200.75);margin:0%200.25rem;color:%23fafafa;padding:0.5rem%201rem;border-radius:0.25rem;width:20rem;position:absolute',
          '.je-header': 'display:inline-block',
          '.je-upload-preview img': 'float:left;margin:0%200.5rem%200.5rem%200;max-width:100%25;max-height:5rem',
          '.je-checkbox': 'display:inline-block;width:auto',
          '.je-checkbox-control--compact': 'display:inline-block;margin-right:1rem',
          '.je-radio': 'display:inline-block;width:auto',
          '.je-radio-control--compact': 'display:inline-block;margin-right:1rem',
          '.je-switcher': 'background-color:transparent;display:inline-block;font-style:italic;font-weight:normal;height:auto;width:auto;margin-bottom:0;margin-left:5px;padding:0%200%200%203px',
          '.je-textarea': 'width:100%25;height:300px;box-sizing:border-box',
          '.je-range-control': 'text-align:center',
          '.je-indented-panel': 'padding-left:10px;margin-left:10px;border-left:1px%20solid%20%23ccc',
          '.je-indented-panel--top': 'padding-left:10px;margin-left:10px',
          '.je-tabholder': 'float:left;width:130px',
          '.je-tabholder .content': 'margin-left:120px',
          '.je-tabholder--top': 'margin-left:10px',
          '.je-tabholder--clear': 'clear:both',
          '.je-tab':
            'border:1px%20solid%20%23ccc;border-width:1px%200%201px%201px;text-align:center;line-height:30px;border-radius:5px;border-bottom-right-radius:0;border-top-right-radius:0;font-weight:bold;cursor:pointer',
          '.je-tab--top':
            'float:left;border:1px%20solid%20%23ccc;border-width:1px%201px%200px%201px;text-align:center;line-height:30px;border-radius:5px;padding-left:5px;padding-right:5px;border-bottom-right-radius:0;border-bottom-left-radius:0;font-weight:bold;cursor:pointer',
          '.je-block-link': 'display:block',
          '.je-media': 'width:100%25',
        };
      function tr(t) {
        return (
          (function(t) {
            if (Array.isArray(t)) return er(t);
          })(t) ||
          (function(t) {
            if (('undefined' != typeof Symbol && null != t[Symbol.iterator]) || null != t['@@iterator']) return Array.from(t);
          })(t) ||
          (function(t, e) {
            if (!t) return;
            if ('string' == typeof t) return er(t, e);
            var r = Object.prototype.toString.call(t).slice(8, -1);
            'Object' === r && t.constructor && (r = t.constructor.name);
            if ('Map' === r || 'Set' === r) return Array.from(t);
            if ('Arguments' === r || /^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(r)) return er(t, e);
          })(t) ||
          (function() {
            throw new TypeError('Invalid attempt to spread non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.');
          })()
        );
      }
      function er(t, e) {
        (null == e || e > t.length) && (e = t.length);
        for (var r = 0, n = new Array(e); r < e; r++) n[r] = t[r];
        return n;
      }
      function rr(t, e) {
        if (!(t instanceof e)) throw new TypeError('Cannot call a class as a function');
      }
      function nr(t, e) {
        for (var r = 0; r < e.length; r++) {
          var n = e[r];
          (n.enumerable = n.enumerable || !1), (n.configurable = !0), 'value' in n && (n.writable = !0), Object.defineProperty(t, n.key, n);
        }
      }
      var ir = (function() {
        function t(e) {
          var r = this,
            n = arguments.length > 1 && void 0 !== arguments[1] ? arguments[1] : {};
          if ((rr(this, t), !(e instanceof Element))) throw new Error('element should be an instance of Element');
          (this.element = e),
            (this.options = f({}, t.defaults.options, n)),
            (this.ready = !1),
            (this.copyClipboard = null),
            (this.schema = this.options.schema),
            (this.template = this.options.template),
            (this.translate = this.options.translate || t.defaults.translate),
            (this.translateProperty = this.options.translateProperty || t.defaults.translateProperty),
            (this.uuid = 0),
            (this.__data = {});
          var i = this.options.theme || t.defaults.theme,
            o = t.defaults.themes[i];
          if (!o) throw new Error('Unknown theme '.concat(i));
          this.element.setAttribute('data-theme', i), (this.theme = new o(this));
          var a = f(Qe, this.getEditorsRules()),
            s = function(t, e, n) {
              return n ? r.addNewStyleRulesToShadowRoot(t, e, n) : r.addNewStyleRules(t, e);
            };
          if (!this.theme.options.disable_theme_rules) {
            var l = m(this.element);
            s('default', a, l), void 0 !== o.rules && s(i, o.rules, l);
          }
          var c = t.defaults.iconlibs[this.options.iconlib || t.defaults.iconlib];
          c && (this.iconlib = new c()), (this.root_container = this.theme.getContainer()), this.element.appendChild(this.root_container);
          var u = document.location.origin + document.location.pathname.toString(),
            h = new N(this.options),
            d = document.location.toString();
          (this.expandSchema = function(t, e) {
            return h.expandSchema(t, e);
          }),
            (this.expandRefs = function(t, e) {
              return h.expandRefs(t, e);
            }),
            (this.refs = h.refs),
            h.load(
              this.schema,
              function(e) {
                var n = r.options.custom_validators ? { custom_validators: r.options.custom_validators } : {};
                r.validator = new P(r, null, n, t.defaults);
                var i = r.getEditorClass(e);
                (r.root = r.createEditor(i, { jsoneditor: r, schema: e, required: !0, container: r.root_container })),
                  r.root.preBuild(),
                  r.root.build(),
                  r.root.postBuild(),
                  v(r.options, 'startval') && r.root.setValue(r.options.startval),
                  (r.validation_results = r.validator.validate(r.root.getValue())),
                  r.root.showValidationErrors(r.validation_results),
                  (r.ready = !0),
                  window.requestAnimationFrame(function() {
                    r.ready && ((r.validation_results = r.validator.validate(r.root.getValue())), r.root.showValidationErrors(r.validation_results), r.trigger('ready'), r.trigger('change'));
                  });
              },
              u,
              d
            );
        }
        var e, r, n;
        return (
          (e = t),
          (r = [
            {
              key: 'getValue',
              value: function() {
                if (!this.ready) throw new Error("JSON Editor not ready yet.  Listen for 'ready' event before getting the value");
                return this.root.getValue();
              },
            },
            {
              key: 'setValue',
              value: function(t) {
                if (!this.ready) throw new Error("JSON Editor not ready yet.  Listen for 'ready' event before setting the value");
                return this.root.setValue(t), this;
              },
            },
            {
              key: 'validate',
              value: function(t) {
                if (!this.ready) throw new Error("JSON Editor not ready yet.  Listen for 'ready' event before validating");
                return 1 === arguments.length ? this.validator.validate(t) : this.validation_results;
              },
            },
            {
              key: 'destroy',
              value: function() {
                this.destroyed ||
                  (this.ready &&
                    ((this.schema = null),
                    (this.options = null),
                    this.root.destroy(),
                    (this.root = null),
                    (this.root_container = null),
                    (this.validator = null),
                    (this.validation_results = null),
                    (this.theme = null),
                    (this.iconlib = null),
                    (this.template = null),
                    (this.__data = null),
                    (this.ready = !1),
                    (this.element.innerHTML = ''),
                    this.element.removeAttribute('data-theme'),
                    (this.destroyed = !0)));
              },
            },
            {
              key: 'on',
              value: function(t, e) {
                return (this.callbacks = this.callbacks || {}), (this.callbacks[t] = this.callbacks[t] || []), this.callbacks[t].push(e), this;
              },
            },
            {
              key: 'off',
              value: function(t, e) {
                if (t && e) {
                  (this.callbacks = this.callbacks || {}), (this.callbacks[t] = this.callbacks[t] || []);
                  for (var r = [], n = 0; n < this.callbacks[t].length; n++) this.callbacks[t][n] !== e && r.push(this.callbacks[t][n]);
                  this.callbacks[t] = r;
                } else t ? ((this.callbacks = this.callbacks || {}), (this.callbacks[t] = [])) : (this.callbacks = {});
                return this;
              },
            },
            {
              key: 'trigger',
              value: function(t, e) {
                if (this.callbacks && this.callbacks[t] && this.callbacks[t].length) for (var r = 0; r < this.callbacks[t].length; r++) this.callbacks[t][r].apply(this, [e]);
                return this;
              },
            },
            {
              key: 'setOption',
              value: function(t, e) {
                if ('show_errors' !== t) throw new Error('Option '.concat(t, ' must be set during instantiation and cannot be changed later'));
                return (this.options.show_errors = e), this.onChange(), this;
              },
            },
            {
              key: 'getEditorsRules',
              value: function() {
                return Object.values(t.defaults.editors).reduce(function(t, e) {
                  return e.rules ? f(t, e.rules) : t;
                }, {});
              },
            },
            {
              key: 'getEditorClass',
              value: function(e) {
                var r;
                if (
                  ((e = this.expandSchema(e)),
                  t.defaults.resolvers.find(function(n) {
                    return (r = n(e)) && t.defaults.editors[r];
                  }),
                  !r)
                )
                  throw new Error('Unknown editor for schema '.concat(JSON.stringify(e)));
                if (!t.defaults.editors[r]) throw new Error('Unknown editor '.concat(r));
                return t.defaults.editors[r];
              },
            },
            {
              key: 'createEditor',
              value: function(e, r) {
                var n = arguments.length > 2 && void 0 !== arguments[2] ? arguments[2] : 1;
                return new e((r = f({}, e.options || {}, r)), t.defaults, n);
              },
            },
            {
              key: 'onChange',
              value: function() {
                var t = this;
                if (this.ready && !this.firing_change)
                  return (
                    (this.firing_change = !0),
                    window.requestAnimationFrame(function() {
                      (t.firing_change = !1),
                        t.ready &&
                          ((t.validation_results = t.validator.validate(t.root.getValue())),
                          'never' !== t.options.show_errors ? t.root.showValidationErrors(t.validation_results) : t.root.showValidationErrors([]),
                          t.trigger('change'));
                    }),
                    this
                  );
              },
            },
            {
              key: 'compileTemplate',
              value: function(e) {
                var r,
                  n = arguments.length > 1 && void 0 !== arguments[1] ? arguments[1] : t.defaults.template;
                if ('string' == typeof n) {
                  if (!t.defaults.templates[n]) throw new Error('Unknown template engine '.concat(n));
                  if (!(r = t.defaults.templates[n]())) throw new Error('Template engine '.concat(n, ' missing required library.'));
                } else r = n;
                if (!r) throw new Error('No template engine set');
                if (!r.compile) throw new Error('Invalid template engine set');
                return r.compile(e);
              },
            },
            {
              key: '_data',
              value: function(t, e, r) {
                if (3 !== arguments.length) return t.hasAttribute('data-jsoneditor-'.concat(e)) ? this.__data[t.getAttribute('data-jsoneditor-'.concat(e))] : null;
                var n;
                t.hasAttribute('data-jsoneditor-'.concat(e)) ? (n = t.getAttribute('data-jsoneditor-'.concat(e))) : ((n = this.uuid++), t.setAttribute('data-jsoneditor-'.concat(e), n)),
                  (this.__data[n] = r);
              },
            },
            {
              key: 'registerEditor',
              value: function(t) {
                return (this.editors = this.editors || {}), (this.editors[t.path] = t), this;
              },
            },
            {
              key: 'unregisterEditor',
              value: function(t) {
                return (this.editors = this.editors || {}), (this.editors[t.path] = null), this;
              },
            },
            {
              key: 'getEditor',
              value: function(t) {
                if (this.editors) return this.editors[t];
              },
            },
            {
              key: 'watch',
              value: function(t, e) {
                return (this.watchlist = this.watchlist || {}), (this.watchlist[t] = this.watchlist[t] || []), this.watchlist[t].push(e), this;
              },
            },
            {
              key: 'unwatch',
              value: function(t, e) {
                if (!this.watchlist || !this.watchlist[t]) return this;
                if (!e) return (this.watchlist[t] = null), this;
                for (var r = [], n = 0; n < this.watchlist[t].length; n++) this.watchlist[t][n] !== e && r.push(this.watchlist[t][n]);
                return (this.watchlist[t] = r.length ? r : null), this;
              },
            },
            {
              key: 'notifyWatchers',
              value: function(t) {
                if (!this.watchlist || !this.watchlist[t]) return this;
                for (var e = 0; e < this.watchlist[t].length; e++) this.watchlist[t][e]();
              },
            },
            {
              key: 'isEnabled',
              value: function() {
                return !this.root || this.root.isEnabled();
              },
            },
            {
              key: 'enable',
              value: function() {
                this.root.enable();
              },
            },
            {
              key: 'disable',
              value: function() {
                this.root.disable();
              },
            },
            {
              key: 'setCopyClipboardContents',
              value: function(t) {
                this.copyClipboard = t;
              },
            },
            {
              key: 'getCopyClipboardContents',
              value: function() {
                return this.copyClipboard;
              },
            },
            {
              key: 'addNewStyleRules',
              value: function(t, e) {
                var r = document.querySelector('#theme-'.concat(t));
                r || ((r = document.createElement('style')).setAttribute('id', 'theme-'.concat(t)), r.appendChild(document.createTextNode('')), document.head.appendChild(r));
                for (var n = r.sheet ? r.sheet : r.styleSheet, i = this.element.nodeName.toLowerCase(); n.cssRules.length > 0; ) n.deleteRule(0);
                Object.keys(e).forEach(function(r) {
                  var o =
                    'default' === t
                      ? r
                      : ''
                          .concat(i, '[data-theme="')
                          .concat(t, '"] ')
                          .concat(r);
                  n.insertRule ? n.insertRule(o + ' {' + decodeURIComponent(e[r]) + '}', 0) : n.addRule && n.addRule(o, decodeURIComponent(e[r]), 0);
                });
              },
            },
            {
              key: 'addNewStyleRulesToShadowRoot',
              value: function(t, e, r) {
                var n = this.element.nodeName.toLowerCase(),
                  i = '';
                Object.keys(e).forEach(function(r) {
                  var o =
                    'default' === t
                      ? r
                      : ''
                          .concat(n, '[data-theme="')
                          .concat(t, '"] ')
                          .concat(r);
                  i += o + ' {' + decodeURIComponent(e[r]) + '}\n';
                });
                var o = new CSSStyleSheet();
                o.replaceSync(i), (r.adoptedStyleSheets = [].concat(tr(r.adoptedStyleSheets), [o]));
              },
            },
          ]) && nr(e.prototype, r),
          n && nr(e, n),
          t
        );
      })();
      (ir.defaults = c),
        (ir.AbstractEditor = M),
        (ir.AbstractTheme = qe),
        (ir.AbstractIconLib = Pe),
        Object.assign(ir.defaults.themes, Ze),
        Object.assign(ir.defaults.editors, je),
        Object.assign(ir.defaults.templates, {}),
        Object.assign(ir.defaults.iconlibs, De);
    },
  ]);
});
